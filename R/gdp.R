library(tidyverse)
library(readxl)
library(reshape2)
library(ggplot2)

#### Задача 0. Нужно загрузить данные
#### https://unstats.un.org/unsd/snaama/downloads
#### нужно GDP and its breakdown at constant 2015 prices in US Dollars
#### Все страны по годам

#загружаем таблицу,определенный лист, пропускаем первые 2 строчки
UN = read_excel('gdp_data.xlsx', sheet="Download-GDPconstant-USD-countr", skip=2)
view(UN)
head(UN)

#### Задача 1А. В категории Final consumption expenditure
#### для каких стран нет пропусков данных?)
#убираем первый столбец, он не нужен
wide_UN = UN
wide_UN = wide_UN[,-1]
head(wide_UN)

#функция melt из пакета reshape2, 
long_UN = melt(wide_UN, id.vars = c("Country", "IndicatorName"), value.vars=4:ncol(UN))

#переименовываем дефолтно заданное название столбца variable
long_UN <- rename(long_UN, Year = variable)

#выделяем подмножество только с индикатором Final Consumption Expenditure
cons = subset(long_UN, IndicatorName == "Final consumption expenditure")

#создаем таблицу с подсчетом по странам по скольким годаем есть данные
missing_by_country = cons %>%
  group_by(Country) %>%
  summarize(available_years=sum(!is.na(value)))%>%
  print()

#### Задача 1B По скольким странам есть данные по всем годам?
# суммируем те страны, где высчитанные значения максимальны (то есть нет пропусков)
sum(missing_by_country$available_years == max(
  missing_by_country$available_years))

#### Задача 2А
#### Нужно выбрать 3 страны с полными данными
#### и создать для них новую переменную Чистый экспортсчитаем для Singapore, Germany, Netherlands
#### Я выбираею США, Брализию и Китай, вы любую другую уникальную комбинацию
# Сначала упростим названия
long_UN$IndicatorName[long_UN$IndicatorName == 
                        "Household consumption expenditure (including Non-profit institutions serving households)"] <- 
  "HH.Expenditure"

long_UN$IndicatorName[long_UN$IndicatorName == 
                        "General government final consumption expenditure"] <- 
  "Gov.Expenditure"

long_UN$IndicatorName[long_UN$IndicatorName == 
                        "Final consumption expenditure"] <-
  "Final.Expenditure"

long_UN$IndicatorName[long_UN$IndicatorName == 
                        "Gross capital formation"] <-
  "Capital"

long_UN$IndicatorName[long_UN$IndicatorName == 
                        "Imports of goods and services"] <-
  "Imports"

long_UN$IndicatorName[long_UN$IndicatorName == 
                        "Exports of goods and services"] <-
  "Exports"

#нам нужно перейти снова к широкому формату (мы берем последнюю таблицу,
#поскольку уже были произведены полезные изменения)
table_UN <- dcast(long_UN, Country + Year ~ IndicatorName)

#считаем чистый экспорт
table_UN$Net.Exports <- 
  table_UN[, "Exports"]-table_UN[, "Imports"]

#мы хотели для трех стран чистый экспорт, поэтому создаем вектор
#Singapore, Germany, Netherlands
sel_countries = c("Singapore", "Germany", "Netherlands")

#выделяем подмножество по найденному вектору
sel_UN1 = subset(table_UN, 
                 subset = (Country %in% sel_countries), 
                 select = c("Country", "Year", "Exports",
                            "Imports", "Net.Exports"))

head(sel_UN1)

#### Задача 3А (строим график) Для двух стран на ваш выбор, я выбрал США и Китай
#### нужно пересчитать значения в миллиарды
# для этого отбираем из С, I, G, NX. нужен длинный формат данных,
# с ним ggplot работает лучше
comp = subset(long_UN, 
              Country %in% c("Singapore", "Netherlands"))

# и пересчитываем в миллиарды долларов значения
comp$value = comp$value / 1e9

#берем только нужные статьи расходов
comp = subset(comp, 
              select = c("Country", "Year",
                         "IndicatorName", "value"),
              subset = IndicatorName %in% c("Gov.Expenditure", 
                                            "HH.Expenditure", "Capital", "Imports", "Exports"))
#### Задача 3B Нужно построить график сравнения для двух стран, по оси x будут года
#### по оси y значения наших статей расходов. разные линии - разные статьи расходов

#сначала сделаем отдельно для Netherlands
#cначала сделаем плоскость
pl_1 = ggplot(subset(comp, Country == "Netherlands"),
            aes(x = Year, y = value))

# затем добавляем линии с группировкой по индикаторам разными цветами
pl_1 = pl_1 + geom_line(aes(group = IndicatorName, 
                        color = IndicatorName), size = 1)

# смотрим что вышло. Какие проблемы?
pl_1

#исправляем
pl_1 = pl_1 + scale_x_discrete(breaks=seq(1970, 2016, by = 10))
pl_1 = pl_1 + scale_y_continuous(name="Billion US$", breaks=seq(0,800, by=50))
pl_1 = pl_1 + ggtitle("GDP components over time")

# тут меняем легенду
pl_1 = pl_1 + scale_colour_discrete(name = "Components of GDP",
                                labels = c("Gross capital formation", "Exports",
                                           "Government expenditure", "Household expenditure",
                                           "Imports")) 
#здесь меняем фон
pl_1 = pl_1 + theme_bw()

#добавляем великую рецессию (с 2007 по 2009 год)
#pl_1 = pl_1 + annotate("text", x = 37, y = 850,
#                   label = "Great Recession")

pl_1

### а теперь для двух стран
# сам график
pl_2 = ggplot(comp, aes(x = Year, y = value, 
                      color = IndicatorName))
pl_2 = pl_2 + geom_line(aes(group = IndicatorName), size = 1)
pl_2 = pl_2 + scale_x_discrete(
  breaks = seq(1970, 2016, by = 10))
pl_2 = pl_2 + scale_y_continuous(name = "Billion US$", breaks=seq(0,800, by=50))
pl_2 = pl_2 + ggtitle("GDP components over time")
pl_2 = pl_2 + scale_colour_discrete(name = "Component")   
pl_2 = pl_2 + theme_bw()

# отдельные графики для каждой из стран
pl_2 = pl_2 + facet_wrap(~Country)
pl_2 = pl_2 + scale_colour_discrete(
  name = "Components of GDP",   
  labels = c("Gross capital formation",  
             "Exports",
             "Government expenditure",
             "Household expenditure",
             "Imports"))
pl_2

##### Задача 4А теперь нам интересны не абсолютные значения, а относительные
##### Для выбранных в задаче 2 стран создать новые колонки
##### с пропорциями статей расходов

#перейдем к широкому виду для наших двух стран
comp_wide <- dcast(comp, Country + Year ~ IndicatorName)
#добавляем чистый экспорт (без широкого вида мы бы не смогли вычесть столбцы
#один из другого)
comp_wide$Net.Exports <- 
  comp_wide[, "Exports"] - comp_wide[, "Imports"]
#убираем лишние экспорт и импорт и снова уходим в длинный формат
comp2_wide <- 
  subset(comp_wide, select = -c(Exports, Imports))
comp2 <-
  melt(comp2_wide, id.vars = c("Year", "Country"))
#новый датафрейм с пропорциями
props = comp2 %>%
  group_by(Country, Year) %>%
  mutate(proportion = value / sum(value))

#### Задача 4B Нужно построить 2 отдельные линейные диаграммы:
#### пропрорции компонентов ВВП по оси y, годы по оси x 
#строим график
pl_3 = ggplot(props, aes(x = Year, y = proportion, 
                       color = variable))

pl_3 = pl_3 + geom_line(aes(group = variable), 
                    size = 1)

pl_3 = pl_3 + scale_x_discrete(breaks = seq(1970, 2016,
                                        by = 10))

pl_3 = pl_3 + ggtitle("GDP component proportions over time")

pl_3 = pl_3 + theme_bw()

# разделяем на отдельные графики
pl_3 = pl_3 + facet_wrap(~Country)
pl_3 = pl_3 + scale_colour_discrete(
  name = "Components of GDP",
  labels = c("Gross capital formation",
             "Government expenditure",
             "Household expenditure", 
             "Net Exports"))
pl_3

#### ЗАДАЧА 5а Если раньше у нас был time-series analysis (анализ временных рядов),
#### то сейчас нам нужно произвести анализ пространственной выборки.
#### Нужно посчитать доли статей расходов ВВП для 2015 года для 9 стран
#мы берем полный вариант данных, уже не comp и снова считаем пропорции
table_UN$p_Capital <- 
  table_UN$Capital / 
  (table_UN$Capital +
     table_UN$Final.Expenditure +
     table_UN$Net.Exports)

table_UN$p_FinalExp <-
  table_UN$Final.Expenditure / 
  (table_UN$Capital +
     table_UN$Final.Expenditure +
     table_UN$Net.Exports)

table_UN$p_NetExports <-
  table_UN$Net.Exports /
  (table_UN$Capital +
     table_UN$Final.Expenditure + 
     table_UN$Net.Exports)

# Создаем вектор с 9 странами: 3 развитые страны, 3 с переходной экономикой
# и 3 развивающиеся. см.:
# https://www.un.org/en/development/desa/policy/wesp/wesp_current/2014wesp_country_classification.pdf

sel_countries_2 <- 
  c("Germany", "Japan", "United States",
    "Albania", "Russian Federation", "Ukraine",
    "Brazil", "China", "India")

#берем широкий формат, выбираем наши 9 стран и высчитанные пропорции
sel_2015 <- 
  subset(table_UN, subset =
           (Country %in% sel_countries_2) & (Year == 2015),
         select = c("Country", "Year", "p_FinalExp",
                    "p_Capital", "p_NetExports"))


# Уходим обратно в длинный формат, чтобы построить график
sel_2015_m <- melt(sel_2015, id.vars = 
                     c("Year", "Country"))

g <- ggplot(sel_2015_m, 
            aes(x = Country, y = value, fill = variable)) + 
  geom_bar(stat = "identity") + coord_flip() +
  ggtitle("GDP component proportions in 2015") +
  scale_fill_discrete(name = "Components of GDP",
                      labels = c("Final expenditure",
                                 "Gross capital formation",
                                 "Net Exports")) +
  theme_bw()

plot(g)

# Перестраиваем строки диаграмы в соответствии с группами (развивающиеся, переходные, развитые) then use ggplot
sel_2015_m$Country <- 
  factor(sel_2015_m$Country, levels = sel_countries_2)

g2 <- ggplot(sel_2015_m, 
            aes(x = Country, y = value, fill = variable)) +
  geom_bar(stat = "identity") + coord_flip() + 
  ggtitle("GDP component proportions in 2015 (ordered)") + 
  scale_fill_discrete(name = "Components of GDP", 
                      labels = c("Final expenditure",
                                 "Gross capital formation",
                                 "Net Exports")) +
  labels = c("Final expenditure",
             "Gross capital formation",
             "Net Exports") +
  theme_bw()

plot(g2)

# другие показатели измерения уровня благосостояния
# https://hbr.org/2012/01/the-economics-of-well-being