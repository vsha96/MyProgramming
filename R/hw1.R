install.packages("nycflights13")
install.packages("dplyr")
install.packages("ggplot2")
library(nycflights13)
library(dplyr)
library(ggplot2)

flights
View(flights)
glimpse(flights)
airlines$name

alaska_flights <- flights %>%
  filter(carrier == "AS")
glimpse(alaska_flights)

portland_flights <- flights %>% 
  filter(dest == "PDX")
View(portland_flights)

# here i'm using vector
some_flights <- flights %>% 
  filter(dest %in% c("PDX", "SEA"))
View(some_flights)

# === the mean ===
View(weather)
summary_temp <- weather %>% 
  summarize(mean = mean(temp), std_dev = sd(temp))
summary_temp
# fix not available data
summary_temp <- weather %>% 
  summarize(mean = mean(temp, na.rm = TRUE),
            std_dev = sd(temp, na.rm = TRUE))
summary_temp

# group_by
summary_monthly_temp <- weather %>% 
  group_by(month) %>%
  summarise(mean = mean(temp, na.rm = TRUE),
            std = sd(temp, na.rm = TRUE))
summary_monthly_temp
# we also have ungroup()