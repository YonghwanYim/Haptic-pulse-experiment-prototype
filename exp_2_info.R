# Project title : Smartwatch Hapticon - Informational Category.
# Author : Yonghwan Yim
# Final Update : 2018.11.19

#install.packages("gplots")
data <- read.csv("C:/Users/uko99/Desktop/info_data.csv", header=T)
data;
library(car) # leveneTest.
library(gplots) # plotmeans.

###### Basic Statistics ######

# Notification Category
noti_data <- data[data$Informational_States == 'Notification', ]; noti_data
noti_mean <- tapply(noti_data$Score, noti_data$Haptic_Pulse, mean); noti_mean
noti_var <- tapply(noti_data$Score, noti_data$Haptic_Pulse, var); noti_var
barplot(noti_mean, main = "Notification Category Mean of Scores", xlab = "Haptic Pulse", ylab = "Score")
#col = c("lightblue", "lightcyan", "lightsteelblue1", "lightskyblue") # barplot color option.

# Active Category
acti_data <- data[data$Informational_States == 'Active', ]; acti_data
acti_mean <- tapply(acti_data$Score, acti_data$Haptic_Pulse, mean); acti_mean
acti_var <- tapply(acti_data$Score, acti_data$Haptic_Pulse, var); acti_var
barplot(acti_mean, main = "Active Category Mean of Scores", xlab = "Haptic Pulse", ylab = "Score")

# Unable category
unab_data <- data[data$Informational_States == 'Unable', ]; unab_data
unab_mean <- tapply(unab_data$Score, unab_data$Haptic_Pulse, mean); unab_mean
unab_var <- tapply(unab_data$Score, unab_data$Haptic_Pulse, var); unab_var
barplot(unab_mean, main = "Unable Category Mean of Scores", xlab = "Haptic Pulse", ylab = "Score")

# Low Energy States category
lowe_data <- data[data$Informational_States == 'Low_Energy_States', ]; lowe_data
lowe_mean <- tapply(lowe_data$Score, lowe_data$Haptic_Pulse, mean); lowe_mean
lowe_var <- tapply(lowe_data$Score, lowe_data$Haptic_Pulse, var); lowe_var
barplot(lowe_mean, main = "Low Energy States Category Mean of Scores", xlab = "Haptic Pulse", ylab = "Score")

# Turning On category
turn_data <- data[data$Informational_States == 'Turning_On', ]; turn_data
turn_mean <- tapply(turn_data$Score, turn_data$Haptic_Pulse, mean); turn_mean
turn_var <- tapply(turn_data$Score, turn_data$Haptic_Pulse, var); turn_var
barplot(turn_mean, main = "Turning On Category Mean of Scores", xlab = "Haptic Pulse", ylab = "Score")


###### Integer Type -> Factor Type ######

noti_data$Haptic_Pulse <- as.factor(noti_data$Haptic_Pulse)
acti_data$Haptic_Pulse <- as.factor(acti_data$Haptic_Pulse)
unab_data$Haptic_Pulse <- as.factor(unab_data$Haptic_Pulse)
lowe_data$Haptic_Pulse <- as.factor(lowe_data$Haptic_Pulse)
turn_data$Haptic_Pulse <- as.factor(turn_data$Haptic_Pulse)


###### Fundamental Assumptions of ANOVA ######

# Shapiro-Wilk Test.
shapiro.test(noti_data$Score) # Normality test of Notification.
shapiro.test(acti_data$Score) # Normality test of Active.
shapiro.test(unab_data$Score) # Normality test of Unable.
shapiro.test(lowe_data$Score) # Normality test of Low Energy States.
shapiro.test(turn_data$Score) # Normality test of Turning On.

# Levene's Test for Homogeneity of Variance.
leveneTest(noti_data$Score, noti_data$Haptic_Pulse) # Notification.
leveneTest(acti_data$Score, acti_data$Haptic_Pulse) # Active.
leveneTest(unab_data$Score, unab_data$Haptic_Pulse) # Unable.
leveneTest(lowe_data$Score, lowe_data$Haptic_Pulse) # Low Energy States.
leveneTest(turn_data$Score, turn_data$Haptic_Pulse) # Turning On.


###### One-way ANOVA ######

# Analysis of Notification.
anova_Notification <- aov(noti_data$Score ~ noti_data$Haptic_Pulse)
summary(anova_Notification)

sd_pooled_calc <- sqrt(anova(anova_Notification)["Residuals", "Mean Sq"]); sd_pooled_calc
mcalc <- mean(noti_data$Score); mcalc
ncalc <- length(noti_data$Score); ncalc
t_crit <- qt(p = .05/2, df = 340, lower.tail = FALSE); t_crit 
confidence_interval <- 2 * ((t_crit * sd_pooled_calc) / sqrt(ncalc)); confidence_interval

# Analysis of Active.
anova_Active <- aov(acti_data$Score ~ acti_data$Haptic_Pulse)
summary(anova_Active)

sd_pooled_calc <- sqrt(anova(anova_Active)["Residuals", "Mean Sq"]); sd_pooled_calc
mcalc <- mean(acti_data$Score); mcalc
ncalc <- length(acti_data$Score); ncalc
t_crit <- qt(p = .05/2, df = 340, lower.tail = FALSE); t_crit 
confidence_interval <- 2 * ((t_crit * sd_pooled_calc) / sqrt(ncalc)); confidence_interval

# Analysis of Unable.
anova_Unable <- aov(unab_data$Score ~ unab_data$Haptic_Pulse)
summary(anova_Unable)

sd_pooled_calc <- sqrt(anova(anova_Unable)["Residuals", "Mean Sq"]); sd_pooled_calc
mcalc <- mean(unab_data$Score); mcalc
ncalc <- length(unab_data$Score); ncalc
t_crit <- qt(p = .05/2, df = 340, lower.tail = FALSE); t_crit 
confidence_interval <- 2 * ((t_crit * sd_pooled_calc) / sqrt(ncalc)); confidence_interval

# Analysis of Low Energy States.
anova_Low_Energy_States <- aov(lowe_data$Score ~ lowe_data$Haptic_Pulse)
summary(anova_Low_Energy_States)

sd_pooled_calc <- sqrt(anova(anova_Low_Energy_States)["Residuals", "Mean Sq"]); sd_pooled_calc
mcalc <- mean(lowe_data$Score); mcalc
ncalc <- length(lowe_data$Score); ncalc
t_crit <- qt(p = .05/2, df = 340, lower.tail = FALSE); t_crit 
confidence_interval <- 2 * ((t_crit * sd_pooled_calc) / sqrt(ncalc)); confidence_interval

# Analysis of Turning On.
anova_Turning_On <- aov(turn_data$Score ~ turn_data$Haptic_Pulse)
summary(anova_Turning_On)

sd_pooled_calc <- sqrt(anova(anova_Turning_On)["Residuals", "Mean Sq"]); sd_pooled_calc
mcalc <- mean(turn_data$Score); mcalc
ncalc <- length(turn_data$Score); ncalc
t_crit <- qt(p = .05/2, df = 340, lower.tail = FALSE); t_crit
confidence_interval <- 2 * ((t_crit * sd_pooled_calc) / sqrt(ncalc)); confidence_interval


###### Post-Hoc Analysis ######

# Tukey Test of Notification.
TukeyHSD(anova_Notification)
#plot(TukeyHSD(anova_Notification))

# Tukey Test of Unable.
TukeyHSD(anova_Unable)

# Tukey Test of Low Energy States.
TukeyHSD(anova_Low_Energy_States)

# Tukey Test of Turning On.
TukeyHSD(anova_Turning_On)


###### Visualization ######

# Mean Plot of Notification
plotmeans(noti_data$Score ~ noti_data$Haptic_Pulse, 
          xlab = "Haptic Pulse",
          p = 0.95,
          ylab = "Score",
          main = "Mean Plot of Notification\n with 95% CI",
          col = "black",
          barwidth = 1,
          barcol = "blue",
          n.label = FALSE,
          use.t = TRUE)
# legends = c("Basic", "Division", "Color", "Division + Color") # X-value label.

