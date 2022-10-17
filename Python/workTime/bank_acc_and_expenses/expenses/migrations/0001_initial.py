# Generated by Django 4.1.2 on 2022-10-16 18:05

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = []

    operations = [
        migrations.CreateModel(
            name="BankAccount",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("account_text", models.CharField(max_length=100)),
                (
                    "creation_date",
                    models.DateTimeField(verbose_name="Date of creation"),
                ),
                ("money", models.IntegerField(default=100)),
            ],
        ),
        migrations.CreateModel(
            name="Ticket",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("ticket_text", models.CharField(max_length=100)),
                ("pub_date", models.DateTimeField(verbose_name="Publication date")),
                ("money", models.IntegerField(default=1)),
                (
                    "account",
                    models.ForeignKey(
                        on_delete=django.db.models.deletion.CASCADE,
                        to="expenses.bankaccount",
                    ),
                ),
            ],
        ),
    ]
