from django.forms import ModelForm

from .models import Ticket, BankAccount


class TicketForm(ModelForm):
    class Meta:
        model = Ticket
        fields = ['ticket_text', 'money']


class AccountForm(ModelForm):
    class Meta:
        model = BankAccount
        fields = ['account_text', 'money']
