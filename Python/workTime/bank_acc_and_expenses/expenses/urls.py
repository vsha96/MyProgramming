from django.urls import path, include

from rest_framework import routers

from . import views
from . import views_rest

app_name = 'expenses'


router = routers.DefaultRouter()
router.register('api/accounts', views_rest.BankAccountViewSet)
router.register('api/tickets', views_rest.TicketViewSet)


urlpatterns = [
    path('', views.IndexView.as_view(), name='index'),
    path('add_account', views.add_account, name='add_account'),
    path('create_account', views.create_account, name='create_account'),
    path('account/<int:account_id>/', views.account_detail, name='detail'),
    path('account/<int:account_id>/add_ticket', views.add_ticket, name='add_ticket'),
    path('account/<int:account_id>/create_ticket', views.create_ticket, name='create_ticket'),
    path('', include(router.urls)),
]