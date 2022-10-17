from django.urls import path

from . import views

app_name = 'expenses'

urlpatterns = [
    path('', views.IndexView.as_view(), name='index'),
    # path('account/<int:pk>/', views.AccountDetailView.as_view(), name='detail'),
    path('account/<int:account_id>/', views.account_detail, name='detail'),
    path('account/<int:account_id>/add_ticket', views.add_ticket, name='add_ticket'),
    path('account/<int:account_id>/create_ticket', views.create_ticket, name='create_ticket'),
]