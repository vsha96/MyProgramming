from django.forms import ModelForm

from .models import Ticket

class TicketForm(ModelForm):
    class Meta:
        model = Ticket
        fields = ['ticket_text', 'money']
