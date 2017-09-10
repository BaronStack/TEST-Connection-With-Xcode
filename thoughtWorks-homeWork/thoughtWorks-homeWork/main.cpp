//
//  main.cpp
//  thoughtWorks-homeWork
//
//  Created by MyFavour on 2017/9/9.
//  Copyright © 2017年 MyFavour. All rights reserved.
//
#include "BOOKING.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <stdlib.h>
#include <cctype>
using namespace std;
const int areaNumber = 4;

struct FourAreaInfo {
    char *name;
    vector<incomeInfo> getResult;
};

//函数成员
bool judgeUserID(char *id) {
    long len = strlen(id);
    int flag = 0;
    if (len != 4)
        return 0;
    else {
        if (isalpha(id[0]))
            flag = 1;
        for (int i = 1;i < len; ++i)
            if (isdigit(id[i]) == 0)
                flag  =0;
    }
    if (flag == 0)
        return 0;
    else
        return 1;
}

int judgeSpecificDayAndGetWeek(int y,int m,int d, itemArea &info) {
    int week,flag = 1;
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m ==12) {
        if (d < 1 || d > 31)
            flag = 0;
    }
    else if (m == 2) {
        if (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && (d < 1 || d > 29))
            flag = 0;
        else if (d < 1 || d > 28)
            flag = 0;
    }
    else if (m == 4 || m == 6 || m == 9 || m == 11) {
        if (d < 1 || d > 30)
            flag = 0;
    }
    else
        flag = 0;
    
    if (flag == 1) {
        week = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7 + 1;
        info.week = week;
        return  week;
    } else
        return 0;
    
}

bool judgeDate(char *date,itemArea &info) {
    long len = strlen(date);
    if (len != 10 || date[4] != '-' || date[7] != '-')
        return  0;
    char sYear[10],sMonth[10],sDay[10];
    sscanf(date, "%[^-]-%[^-]-%[^-]",sYear,sMonth,sDay);
    if(judgeSpecificDayAndGetWeek(atoi(sYear),atoi(sMonth),atoi(sDay),info)) {
        info.day = atoi(sDay);
        info.month = atoi(sMonth);
        info.year = atoi(sYear);
        return 1;
    }
    else
        return 0;
}

int caculatePrice(itemArea &info) {
    if(info.week >= 1 && info.week <= 5 ) {
        if(info.hourDown >= 9 && info.hourDown <= 12) {
            if(info.hourUp >= 9 && info.hourUp <= 12)
                info.income = (info.hourUp - info.hourDown) * 30;
            else if(info.hourUp > 12 && info.hourUp <= 18)
                info.income = (12 - info.hourDown) * 30 + (info.hourUp - 12) * 50;
            else if (info.hourUp > 18 && info.hourUp <= 20)
                info.income = (12 - info.hourDown) * 30 + 50 * 6 + (info.hourUp - 18) * 80;
            else
                info.income = (12 - info.hourDown) * 30 + 50 * 6 + 80 * 2 + (info.hourUp - 20) * 60;
        }
        else if(info.hourDown > 12 && info.hourDown <= 18) {
            if(info.hourUp > 12 && info.hourUp <= 18)
                info.income = (info.hourUp - info.hourDown) * 50;
            else if (info.hourUp > 18 && info.hourUp <= 20)
                info.income = (18 - info.hourDown) * 50 + (info.hourUp - 18) * 80;
            else
                info.income = (18 - info.hourDown) * 50 + 80 * 2 + (info.hourUp - 20) * 60;
        }
        else if (info.hourDown > 18 && info.hourDown <= 20) {
            if (info.hourUp > 18 && info.hourUp <= 20)
                info.income = (info.hourUp - info.hourDown) * 80;
            else if (info.hourUp > 20 && info.hourUp <= 22)
                info.income = (20 - info.hourDown) * 80 + (info.hourUp - 20) * 60;
        }
        else
            info.income = (info.hourUp - info.hourDown) * 60;
    } else {
        if(info.hourDown >= 9 && info.hourDown < 12) {
            if(info.hourUp >=9 && info.hourUp < 12)
                info.income = (info.hourUp - info.hourDown) * 40;
            else if(info.hourUp >= 12 && info.hourUp < 18)
                info.income = (12 - info.hourDown) * 40 + (info.hourUp - 12) * 50;
            else
                info.income = (12 - info.hourDown) * 40 + 50 * 6 + (info.hourUp - 18) * 60;
        }
        else if(info.hourDown >=12 && info.hourDown < 18) {
            if(info.hourUp >= 12 && info.hourUp < 18)
                info.income = (info.hourUp - info.hourDown) * 50;
            else
                info.income = (18 - info.hourDown) * 50 + (info.hourUp - 18) * 60;
        }
        else
            info.income = (info.hourUp - info.hourDown) * 60;
    }
    return info.income;
    
}

int judgeSpecificTimeAndGetHours(int h1,int m1, int h2, int m2,itemArea &info) {
    if (h1 >= h2 || h1 < 9 || h2 > 22)
        return 0;
    else
        return caculatePrice(info);
}

bool judgeTime(char *time,itemArea &info) {
    long len = strlen(time);
    if (len == 0 || time[2] != ':' || time[5] != '~' || time[8] != ':')
        return 0;
    char hourLeft[5],minuteLeft[5],hourRight[5],minuteRight[5];
    sscanf(time, "%[^:]:%[^~]~%[^:]:%s",hourLeft,minuteLeft,hourRight,minuteRight);
    info.hourDown = atoi(hourLeft);
    info.hourUp = atoi(hourRight);
    if(strcmp(minuteRight,"00") || strcmp(minuteLeft, "00"))
        return 0;
    else {
        if(judgeSpecificTimeAndGetHours(atoi(hourLeft), atoi(minuteLeft), atoi(hourRight), atoi(minuteRight) ,info)) {
           return 1;
        } else
            return 0;
    }
}

bool judgeBookingArea(char *area) {
    long len = strlen(area);
    if (len > 1 || area[0] < 'A' || area[0] > 'D')
        return 0;
    else
        return 1;
}

bool judgeCancle(char *cancle) {
    if (strcmp(cancle,"C"))
        return 1;
    else
        return 0;
}

bool judgeModelCorrect(incomeInfo &inputs) {
    if (judgeUserID(inputs.userID) && judgeDate(inputs.bookingDate,inputs.TotalHour) && judgeTime(inputs.bookingTime,inputs.TotalHour) && judgeBookingArea(inputs.bookingArea)) {
        if(inputs.cancleBooking == NULL)
            return 1;
        else if(judgeCancle(inputs.cancleBooking))
            return 0;
        else
            return 1;
    }
    else
        return 0;
}

int findDateConflicts(char *infoDate,char *inputsDate) {
    return (strcmp(infoDate, inputsDate) == 0)? 0:1;
}

int findTimeConficts(incomeInfo infoTime, incomeInfo inputs) {
    if(inputs.TotalHour.hourDown > infoTime.TotalHour.hourDown && inputs.TotalHour.hourDown < infoTime.TotalHour.hourUp)
        return 1;
    else if(inputs.TotalHour.hourUp > infoTime.TotalHour.hourDown && inputs.TotalHour.hourUp < infoTime.TotalHour.hourUp)
        return 1;
    else
        return 0;
}


int findConflicts(FourAreaInfo (&info)[4],incomeInfo inputs) {
    for (int i = 0;i < 4; ++ i) {
        if(strcmp(info[i].name, inputs.bookingArea) == 0) {
            if(info[i].getResult.size() > 1) {
                for (int j = 0;j < info[i].getResult.size(); ++j) {
                    if(inputs.cancleBooking != NULL) {
                        if(info[i].getResult[j].cancleBooking != NULL && strcmp(inputs.bookingArea, info[i].getResult[j].bookingArea) == 0 && strcmp(inputs.bookingDate, info[i].getResult[j].bookingDate) == 0 && strcmp(inputs.bookingTime, info[i].getResult[j].bookingTime) == 0 && strcmp(inputs.userID, info[i].getResult[j].userID)== 0)
                            return  2;
                        else
                            return -1;
                    } else {
                        if (findDateConflicts(info[i].getResult[j].bookingDate, inputs.bookingDate))
                            return 1;
                        else
                        {
                            if(strcmp(info[i].getResult[j].userID, inputs.userID) == 0 && strcmp(info[i].getResult[j].bookingTime, inputs.bookingTime) == 0)
                                return -2;
                            else if(strcmp(info[i].getResult[j].userID, inputs.userID) == 0 && findTimeConficts(info[i].getResult[j],inputs))
                                return -2;
                            else
                                return 1;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

incomeInfo divideInputs(char inputs[]) {
    Booking buff;
    char * s[20];
    for (int i = 0;i < 10; ++i)
        s[i] = (char *) malloc(10 *sizeof(char));
    s[0] = strtok(inputs, " ");
    int len = 1;
    while(s[len] != NULL) {
        s[len] = strtok(NULL, " ");
        len ++;
    }
    buff.userID = s[0];
    buff.bookingDate = s[1];
    buff.bookingTime = s[2];
    buff.bookingArea = s[3];
    buff.cancleBooking = s[4];
    return  buff;
}

void printInfo(FourAreaInfo (&info)[4]) {
    cout << "收入汇总\n---\n";
    int total[4] = {0};
    for (int i = 0;i < 4; ++i) {
        printf("场地：%s\n",info[i].name);
        if(info[i].getResult.size() >= 1) {
            for (vector<incomeInfo>::iterator it  = info[i].getResult.begin(); it != info[i].getResult.end(); ++it) {
                if((*it).cancleBooking == NULL) {
                    printf("%s %s %d元\n",(*it).bookingDate,(*it).bookingTime,(*it).TotalHour.income);
                    total[i] += (*it).TotalHour.income;
                }
                else {
                    printf("%s %s 违约金 %.2f元\n",(*it).bookingDate,(*it).bookingTime,(((*it).TotalHour.week > 5 && (*it).TotalHour.week < 7) ? 0.25:0.5) * (*it).TotalHour.income);
                    total[i] += (((*it).TotalHour.week > 5 && (*it).TotalHour.week < 7) ? 0.25:0.5) * (*it).TotalHour.income;
                }
            }
            printf("小计：%d元\n",total[i]);
        } else {
            printf("小计：0元\n");
        }
        if(i != 3)
            printf("\n");
    }
    int sum = 0;
    for (int i = 0;i < 4; ++i)
        sum += total[i];
    printf("---\n总计：%d元\n",sum);
}

int main(int argc, const char * argv[]) {
    FourAreaInfo info[areaNumber];
    incomeInfo buffInfo,temp;
    info[0].name = (char *)malloc(sizeof(char));
    info[0].name[0] = 'A';
    for (int i = 0;i < areaNumber; ++i) {
        info[i].name = (char *)malloc(sizeof(char));
        info[i].name[0] = char (i + 65);
    }
    char inputs[50],outputs[50];
    memset(inputs, 0x00, sizeof(inputs));
    while(true) {
        char buff;
        int i = 0;
        while((buff = getchar()) != '\n' )
            inputs[i++] = buff;
        if(buff == '\n' && strcmp(inputs,outputs) == 0) {
            printInfo(info);
        }
        else {
            buffInfo = divideInputs(inputs);
            if (judgeModelCorrect(buffInfo)) {
                int condition = findConflicts(info, buffInfo);
                switch (condition) {
                    case 1:
                        temp = buffInfo;
                        info[buffInfo.bookingArea[0] - 'A'].getResult.push_back(buffInfo);
                        cout << "Success: the booking is accepted!" << endl;
                        break;
                    case 2:
                        for (vector<incomeInfo>::iterator it = info[buffInfo.bookingArea[0] - 'A'].getResult.begin(); it != info[buffInfo.bookingArea[0] - 'A'].getResult.end(); ++it)
                            if((*it).cancleBooking != NULL && strcmp(buffInfo.bookingArea, (*it).bookingArea) == 0 && strcmp(buffInfo.bookingDate, (*it).bookingDate) == 0 && strcmp(buffInfo.bookingTime, (*it).bookingTime) == 0 && strcmp(buffInfo.userID, (*it).userID)== 0) {
                                if((*it).TotalHour.week >= 1 && (*it).TotalHour.week <= 5)
                                    (*it).TotalHour.income *= 0.5;
                                else
                                    (*it).TotalHour.income *= 0.25;
                            }
                        cout << "Success: the booking is accepted!" << endl;
                        break;
                    case -1:
                        cout << "Error: the booking being cancelled does not exist!" << endl;
                        break;
                    case -2:
                        cout << "Error: the booking conflicts with existing bookings!" << endl;
                        break;
                    default:
                        break;
                }
            }
            else
                cout << "Error :the booking is invalid" << endl;
        }
        for(int i = 0;i < strlen(inputs); ++i)
            outputs[i] = inputs[i];
    }
    return 0;
}
