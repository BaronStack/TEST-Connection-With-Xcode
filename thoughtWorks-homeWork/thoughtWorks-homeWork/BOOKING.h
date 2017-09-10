//
//  BOOKING.h
//  thoughtWorks-homeWork
//
//  Created by MyFavour on 2017/9/10.
//  Copyright © 2017年 MyFavour. All rights reserved.
//

#ifndef BOOKING_h
#define BOOKING_h
typedef struct TimeAndDate {
    int week;
    int year,month,day,hourUp,hourDown,minute;
    
    int totalHour = 0;
    int income = 0;
}itemArea;

typedef struct Booking{
    char *userID = nullptr;
    char *bookingDate = nullptr;
    char *bookingTime = nullptr;
    char *bookingArea = nullptr;
    char *cancleBooking = nullptr;
    int littleSum = 0;
    itemArea TotalHour;
}incomeInfo;


#endif /* BOOKING_h */
