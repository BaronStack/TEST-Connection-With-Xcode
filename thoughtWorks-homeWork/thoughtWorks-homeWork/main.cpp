//
//  main.cpp
//  thoughtWorks-homeWork
//
//  Created by MyFavour on 2017/9/9.
//  Copyright © 2017年 MyFavour. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
const int areaNumber = 4;

typedef struct TimeAndDate {
    int week;
    int year,month,day,hourUp,hourDown,minute;
    
    int totalHour = 0;
}itemArea;

typedef struct Booking{
    char *userID;
    char *bookingDate;
    char *bookingTime;
    char bookingArea;
    bool ifBreakLaw = 0;
    int income = 0;
    itemArea TotalHour;
}incomeInfo;

struct FourArea {
    char name;
    vector<incomeInfo> getResult;
};



bool judgeModel(char *inputs) {
    return 1;
}

void printInfo(FourArea *info,int ) {
    printf("收入汇总\n---\n场地：A\n2016-06-02 09:00~10:00 违约金 15元\n2016-06-02 10:00~12:00 60元\n2016-06-03 20:00~22:00 120元\n小计：195元\n\n场地:B\n2016-06-04 09:00~10:00 40元\n小计：40元\n\n场地：C\n小计：0元\n\n场地：D\n小计：0元\n---\n总计：235元\n");
}

int main(int argc, const char * argv[]) {
    FourArea info[areaNumber];
    while(true) {
        char buff;
        char inputs[100] = "";
        int i = 0;
        while((buff = getchar()) != '\n' )
            inputs[i++] = buff;
        if(buff == '\n' && strlen(inputs) == 0)
            printInfo(info, areaNumber);
        else {
                
        }
    }
    return 0;
}
