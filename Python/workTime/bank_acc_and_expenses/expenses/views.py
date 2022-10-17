from django.core.exceptions import ValidationError
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404
from django.urls import reverse

from django.views import generic
from django.utils import timezone

from .models import BankAccount, Ticket
from .forms import TicketForm


class IndexView(generic.ListView):
    template_name = 'expenses/index.html'
    context_object_name = 'bank_account_list'

    def get_queryset(self):
        """Return all bank accounts ordered by creation date."""
        return BankAccount.objects.order_by('creation_date')

# class AccountDetailView(generic.DetailView):
#     model = BankAccount
#     template_name = 'expenses/account_index.html'

def account_detail(request, account_id):
    account = get_object_or_404(BankAccount, pk=account_id)
    ticket_list = account.ticket_set.order_by('-pub_date')

    return render(
        request,
        'expenses/account_index.html', 
        {'account': account
            ,'ticket_list': ticket_list})

def add_ticket(request, account_id):
    account = get_object_or_404(BankAccount, pk=account_id)
    ticket_form = TicketForm()
    return render(
        request, 
        'expenses/add_ticket.html',
        {'account': account,
        'form': ticket_form})

def create_ticket(request, account_id):
    account = get_object_or_404(BankAccount, pk=account_id)
    try:
        new_ticket = Ticket()
        new_ticket.account = account
        new_ticket.ticket_text = request.POST['ticket_text']
        new_ticket.pub_date = timezone.now()
        new_ticket.money = request.POST['money']
        new_ticket.clean()

    except ValidationError as err:
        # Redisplay the ticket creation form.
        ticket_form = TicketForm()

        return render(request, 'expenses/add_ticket.html', {
            'account': account,
            'error_message': err.message,
            'form': ticket_form
        })
    else:
        new_ticket.save()
        # Always return an HttpResponseRedirect after successfully dealing
        # with POST data. This prevents data from being posted twice if a
        # user hits the Back button.
        return HttpResponseRedirect(reverse('expenses:detail', args=(account.id,)))

    # return HttpResponse('Created a ticket!')


