library(tidyverse)
library(ISLR)
library(moderndive)
library(skimr)

# get our data and rename columns
credit_ch6 <- Credit %>% as_tibble() %>%
  select(ID, debt = Balance, credit_limit = Limit, 
         income = Income, credit_rating = Rating, age = Age)

# random sample with size...
credit_ch6 %>% sample_n(size = 5)

# wanna see a statistics
credit_ch6 %>% select(debt, credit_limit, income) %>% skim

# correlation matrix
credit_ch6 %>% 
  select(debt, credit_limit, income) %>% 
  cor()

# visualization
ggplot(credit_ch6, aes(x = credit_limit, y = debt)) +
  geom_point() +
  labs(x = "Credit limit (in $)", y = "Credit card debt (in $)", 
       title = "Debt and credit limit") +
  geom_smooth(method = "lm", se = FALSE)

ggplot(credit_ch6, aes(x = income, y = debt)) +
  geom_point() +
  labs(x = "Income (in $1000)", y = "Credit card debt (in $)", 
       title = "Debt and income") +
  geom_smooth(method = "lm", se = FALSE)

# LC6.2
credit_ch6 %>% 
  select(debt, credit_rating, age) %>% 
  cor()
# ANSWER: we can see that debt and credit rating has no relation 
# with the age of cardholders

# Fit regression model:
debt_model <- lm(debt ~ credit_limit + income, data = credit_ch6)
# Get regression table:
get_regression_table(debt_model)

# LC6.3
debt_model1 <- lm(debt ~ credit_rating + age, data = credit_ch6)
get_regression_table(debt_model1)
# ANSWER: debt = -$270 + 2.6*rating - 2.4*age

get_regression_points(debt_model)


