library(tidyverse)
library(readxl)
library(reshape2)
library(ggplot2)

cdata = read_excel('hdi.xlsx', sheet="Table 1", skip=4)
view(cdata)

#life_e = subset(cdata, select = c("...2", "Life expectancy at birth"))
life_e = cdata[5]
view(life_e)

maxlife = max(life_e[], na.rm=TRUE)
