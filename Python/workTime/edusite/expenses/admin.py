from django.contrib import admin
from django.template.response import TemplateResponse
from django.urls import path
from django.http import HttpResponse

from .models import BankAccount, Ticket


class TicketInline(admin.TabularInline):
    model = Ticket
    extra = 3



class TicketAdmin(admin.ModelAdmin):
    search_fields = ['ticket_text', 'money']

    list_display = ('account', 'ticket_text', 'pub_date', 'money')
    list_filter = ['account', 'money']

    list_per_page = 10


class BankAccountAdmin(admin.ModelAdmin):
    search_fields = ['account_text']

    list_display = ('account_text', 'creation_date', 'money')
    list_filter = ['creation_date']

    fieldsets = [
        (None, {'fields': ['account_text', 'money']}),
        ('Date Information', 
            {'fields': ['creation_date']
            ,'classes': ['collapse']}),
    ]

    inlines = [TicketInline]

    # def get_urls(self):
    #     urls = super().get_urls()
    #     my_urls = [
    #         path('reports/', self.test_view, name='test_view'),
    #     ]
    #     return my_urls + urls

    # def test_view(self, request):
    #     return HttpResponse('REPORT FORM')


# class AdminSiteReports(admin.AdminSite):
#     def get_urls(self):
#         urls = super().get_urls()
#         my_urls = [
#             path('reports/', self.test_view, name='test_view'),
#         ]
#         return my_urls + urls

    
# def test_view(self, request):
#         return HttpResponse('REPORT FORM')


# admin_reports = AdminSiteReports(name="admin-reports")

admin.site.register(BankAccount, BankAccountAdmin)
admin.site.register(Ticket, TicketAdmin)


