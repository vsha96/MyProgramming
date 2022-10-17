from django.db import models
from django.db.models import F
from django.utils.translation import gettext_lazy as _
from django.core.exceptions import ValidationError

from .validators import validate_money


class BankAccount(models.Model):
    account_text = models.CharField(max_length=100)
    creation_date = models.DateTimeField('Date of creation')
    money = models.IntegerField(default=100)

    def __str__(self):
        return f'''Bank account #{self.pk}
            {self.account_text} 
            ({self.creation_date.strftime("%Y-%m-%d")}) 
            with ${str(self.money)}'''

    def can_spend_money(self, asked_money):
        return self.money > 0 and int(asked_money) <= self.money

    def spend_money(self, asked_money):
        if self.can_spend_money(asked_money):
            # avoid race condition via F()
            self.money = F('money') - int(asked_money)
            self.save()


class Ticket(models.Model):
    account = models.ForeignKey(BankAccount, on_delete=models.CASCADE)
    ticket_text = models.CharField(max_length=100)
    pub_date = models.DateTimeField('Publication date')
    money = models.IntegerField(default=1, validators=[validate_money])

    def __str__(self):
        return f'''<{self.pub_date.strftime("%Y-%m-%d %H:%M:%S")}> 
            #{str(self.pk)} 
            {self.ticket_text} -- ${self.money}'''

    def clean(self):
        super().clean()
        if not self.account.can_spend_money(self.money):
            raise ValidationError(_('Not enough money on the account balance.'))

    def save(self, *args, **kwargs):
        self.clean()
        self.account.spend_money(self.money)
        super(Ticket, self).save(*args, **kwargs)



