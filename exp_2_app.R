# Project title : Smartwatch Hapticon - Application.
# Author : Yonghwan Yim
# Final Update : 2018.11.19

#install.packages("gplots")
data <- read.csv("C:/Users/uko99/Desktop/app_data.csv", header=T)
data;
library(car) # leveneTest.
library(gplots) # plotmeans.

###### Basic Statistics ######

# E-mail
mail_data <- data[data$Application == 'E_Mail', ]; mail_data
mail_mean <- tapply(mail_data$Score, mail_data$Haptic_Pulse, mean); mail_mean

# IM
im_data <- data[data$Application == 'IM', ]; im_data
im_mean <- tapply(im_data$Score, im_data$Haptic_Pulse, mean); im_mean

# Call
call_data <- data[data$Application == 'Call', ]; call_data
call_mean <- tapply(call_data$Score, call_data$Haptic_Pulse, mean); call_mean

# Health Care
health_data <- data[data$Application == 'Health_Care', ]; health_data
health_mean <- tapply(health_data$Score, health_data$Haptic_Pulse, mean); health_mean


###### Integer Type -> Factor Type ######

mail_data$Haptic_Pulse <- as.factor(mail_data$Haptic_Pulse)
im_data$Haptic_Pulse <- as.factor(im_data$Haptic_Pulse)
call_data$Haptic_Pulse <- as.factor(call_data$Haptic_Pulse)
health_data$Haptic_Pulse <- as.factor(health_data$Haptic_Pulse)


###### Fundamental Assumptions of ANOVA ######

# Shapiro-Wilk Test.
shapiro.test(mail_data$Score) # Normality test of E-Mail.
shapiro.test(im_data$Score) # Normality test of IM.
shapiro.test(call_data$Score) # Normality test of Call.
shapiro.test(health_data$Score) # Normality test of Health Care.

# Levene's Test for Homogeneity of Variance.
leveneTest(mail_data$Score, mail_data$Haptic_Pulse) # E-Mail.
leveneTest(im_data$Score, im_data$Haptic_Pulse) # IM.
leveneTest(call_data$Score, call_data$Haptic_Pulse) # Call.
leveneTest(health_data$Score, health_data$Haptic_Pulse) # Health Care.


###### One-way ANOVA ######

# Analysis of E-Mail.
anova_Mail <- aov(mail_data$Score ~ mail_data$Haptic_Pulse)
summary(anova_Mail)

sd_pooled_calc <- sqrt(anova(anova_Mail)["Residuals", "Mean Sq"]); sd_pooled_calc
mcalc <- mean(mail_data$Score); mcalc
ncalc <- length(mail_data$Score); ncalc
t_crit <- qt(p = .05/2, df = 340, lower.tail = FALSE); t_crit
confidence_interval <- 2 * ((t_crit * sd_pooled_calc) / sqrt(ncalc)); confidence_interval

# Analysis of IM.
anova_IM <- aov(im_data$Score ~ im_data$Haptic_Pulse)
summary(anova_IM)

sd_pooled_calc <- sqrt(anova(anova_IM)["Residuals", "Mean Sq"]); sd_pooled_calc
mcalc <- mean(im_data$Score); mcalc
ncalc <- length(im_data$Score); ncalc
t_crit <- qt(p = .05/2, df = 340, lower.tail = FALSE); t_crit
confidence_interval <- 2 * ((t_crit * sd_pooled_calc) / sqrt(ncalc)); confidence_interval

# Analysis of Call.
anova_Call <- aov(call_data$Score ~ call_data$Haptic_Pulse)
summary(anova_Call)

sd_pooled_calc <- sqrt(anova(anova_Call)["Residuals", "Mean Sq"]); sd_pooled_calc
mcalc <- mean(call_data$Score); mcalc
ncalc <- length(call_data$Score); ncalc
t_crit <- qt(p = .05/2, df = 340, lower.tail = FALSE); t_crit
confidence_interval <- 2 * ((t_crit * sd_pooled_calc) / sqrt(ncalc)); confidence_interval

# Analysis of Health Care.
anova_Health <- aov(health_data$Score ~ health_data$Haptic_Pulse)
summary(anova_Health)

sd_pooled_calc <- sqrt(anova(anova_Health)["Residuals", "Mean Sq"]); sd_pooled_calc
mcalc <- mean(health_data$Score); mcalc
ncalc <- length(health_data$Score); ncalc
t_crit <- qt(p = .05/2, df = 340, lower.tail = FALSE); t_crit
confidence_interval <- 2 * ((t_crit * sd_pooled_calc) / sqrt(ncalc)); confidence_interval


###### Post-Hoc Analysis ######

# Tukey Test of E-Mail.
TukeyHSD(anova_Mail)

# Tukey Test of IM.
TukeyHSD(anova_IM)

# Tukey Test of Call.
TukeyHSD(anova_Call)

