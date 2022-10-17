from django.contrib import admin

from .models import BankAccount, Ticket


class TicketInline(admin.TabularInline):
    model = Ticket
    extra = 3


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


admin.site.register(BankAccount, BankAccountAdmin)