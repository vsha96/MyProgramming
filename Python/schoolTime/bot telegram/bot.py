# -*- coding: utf-8 -*-
import config
import telebot
from pymystem3 import Mystem
from telebot.types import ReplyKeyboardMarkup, ReplyKeyboardRemove
from telebot import types
from config import categories,themes
from collections import Counter
bot = telebot.TeleBot(config.token)

@bot.message_handler(commands=["start"])
def hello(message):
    bot.send_message(message.chat.id, 'Привет! Я - бот:) Я умею обрабатывать запросы, связанные с финансовой деятельностью. Например, мне можно задать вопрос "Где находится ближаший банкомат?". Напишите, что вас интересует.')

@bot.message_handler(content_types="text")
def loyal(message):
    keyboard = types.ReplyKeyboardMarkup()
    keyboard.row('yes', 'no')
    if message.text == 'да':
        bot.send_message(message.chat.id, "Что да?")
        pass
    elif message.text == 'нет':
        bot.send_message(message.chat.id, "Что нет?")
        pass
    elif message.text == 'привет':
        bot.send_message(message.chat.id, "Здравствуйте =)")
        pass
    elif j == 0:
        ls[i] = m.lemmatize(ls[i])
        if ls[i][0] in thema0:
            bot.send_message(message.chat.id, 'Вас интересует "Адреса офисов и банкоматов". Да?')
            j = 1
        elif ls[i][0] in thema1:
            bot.send_message(message.chat.id, 'Вас интересует "Акции". Да?')
            j = 1
        elif ls[i][0] in thema2:
            bot.send_message(message.chat.id, 'Вас интересует "Блокировка карты". Да?')
            j = 1
        elif ls[i][0] in thema3:
            bot.send_message(message.chat.id, 'Вас интересует "Вам звонили". Да?')
            j = 1
        elif ls[i][0] in thema4:
            bot.send_message(message.chat.id, 'Вас интересует "Вклад". Да?')
            j = 1
        elif ls[i][0] in thema5:
            bot.send_message(message.chat.id, 'Вас интересует "Действующие кредиты". Да?')
            j = 1
        elif ls[i][0] in thema6:
            bot.send_message(message.chat.id, 'Вас интересует "Денежные преводы". Да?')
            j = 1
        elif ls[i][0] in thema7:
            bot.send_message(message.chat.id, 'Вас интересует "Задолженность". Да?')
            j = 1
        elif ls[i][0] in thema8:
            bot.send_message(message.chat.id, 'Вас интересует "Интернет банк". Да?')
            j = 1
        else:
            if j == 0 and i == len(ls):
                bot.send_message(message.chat.id, "Повторите запрос")

@bot.message_handler(content_types=['sticker'])
def other_message(message):
    bot.send_message(message.chat.id, 'Ха-ха')


if __name__ == '__main__':
    bot.polling(none_stop=True)
