from django.shortcuts import get_object_or_404
from django.utils import timezone


from .models import BankAccount, Ticket
from .serializers import BankAccountSerializer, TicketSerializer

from rest_framework.decorators import api_view
from rest_framework import viewsets
from rest_framework import permissions
from rest_framework.response import Response


class BankAccountViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows bank accounts to be viewed or edited.
    """
    queryset = BankAccount.objects.order_by('-creation_date')
    serializer_class = BankAccountSerializer
    permission_classes = [permissions.AllowAny]        


class  TicketViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows tickets to be viewed or edited.
    """
    queryset = Ticket.objects.order_by('-pub_date')
    serializer_class = TicketSerializer
    permission_classes = [permissions.AllowAny]

    # def get_queryset(self):
    #     ticket_id = self.request.query_params.get("id", None)
    #     if ticket_id:
    #         ticket = get_object_or_404(Ticket, pk=ticket_id)
    #         return ticket

    #     return super().get_queryset()


