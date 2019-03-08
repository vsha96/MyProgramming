# -*- coding: utf-8 -*-
import config
import telebot
from pymystem3 import Mystem
import sys
from telebot.types import ReplyKeyboardMarkup, KeyboardButton

bot = telebot.TeleBot(config.token)

thema0 = ['банка', 'адрес', 'банкомат', 'отделение', 'город', 'офис', 'банк', 'филиал', 'снять', 'деньги', 'близкий', 'близко', 'недалеко', 'находиться', 'находить', 'улица', 'ваш', 'снятие', 'обмен', 'аппарат']
thema1 = ['акция']
thema2 = ['заблокировать', 'карта', 'блокировка', 'блокировать', 'украсть', 'карточка', 'нужно']
thema3 = ['звонить', 'звонок', 'позвонить', 'телефон', 'номер', 'перезванивать', 'перезвонить', 'вызов', 'сказать', 'связь', 'абонент', 'оператор']
thema4 = ['вклад','вложить']
thema5 = ['кредит','действующий']
thema6 = ['перевод','перевести']
thema7 = ['задолженность']
thema8 = ['интернет','личный','кабинет']

@bot.message_handler(commands=["start"])
def hello(message):
    bot.send_message(message.chat.id, 'Привет! Я - бот:) Я умею обрабатывать запросы, связанные с финансовой деятельностью. Например, мне можно задать вопрос "Где находится ближаший банкомат?". Напишите, что вас интересует.')

@bot.message_handler(content_types=["text"])
def recieve_message(message):
    ls = message.text.lower().strip('\n').split()
    m = Mystem()
    j = 0
    for i in range(len(ls)):
        if j == 0:
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
    #bot.send_message(message.chat.id, "Спасибо за запрос. Он обязательно будет обработан:)")

if __name__ == '__main__':
    bot.polling(none_stop=True)
