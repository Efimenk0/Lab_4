//
//  TestsForApartments.m
//  TestsForApartments
//
//  Created by Константин Ефименко on 09.02.2021.
//

#import <XCTest/XCTest.h>
#import "Apartments.h"

using namespace FundClass;

@interface TestsForApartments : XCTestCase

@end

@implementation TestsForApartments


- (void)testConstructors {
    Apartments ap;
    XCTAssertEqual("undefined", ap.get_street());
    XCTAssertEqual(0, ap.get_countOfRooms());
    XCTAssertEqual(-1, ap.get_number());
    XCTAssertEqualWithAccuracy(0, ap.get_area(), 0.0001);
    Apartments ap2("Mira");
    XCTAssertEqual("Mira", ap2.get_street());
    XCTAssertEqual(0, ap2.get_countOfRooms());
    XCTAssertEqual(-1, ap2.get_number());
    XCTAssertEqualWithAccuracy(0, ap2.get_area(), 0.0001);
}

- (void)testSetNumber {
    Apartments ap("Mira");
    XCTAssertNoThrow(ap.set_number(5));
    XCTAssertEqual(5, ap.get_number());
    XCTAssertThrows(ap.set_number(-1));
}

- (void)testAddDeleteSelectRoom {
    Apartments ap("Mira");
    XCTAssertNoThrow(ap.set_number(5));
    Room r1("hall");
    XCTAssertNoThrow(r1.set_area(12));
    XCTAssertNoThrow(ap.add_room(r1));
    XCTAssertEqual(1, ap.get_countOfRooms());
    XCTAssertEqualWithAccuracy(12, ap.get_area(), 0.01);
    XCTAssertThrows(ap.select_room(2));
    XCTAssertThrows(ap.select_room(-1));
    XCTAssertEqual("hall", ap.select_room(1).get_name());
    Room r2("kitchen");
    XCTAssertNoThrow(r2.set_remark("This is kitchen").set_area(20));
    XCTAssertNoThrow(ap.add_room(r2));
    XCTAssertEqual(2, ap.get_countOfRooms());
    XCTAssertEqualWithAccuracy(32, ap.get_area(), 0.01);
    XCTAssertEqual("kitchen", ap.select_room(2).get_name());
    XCTAssertEqual("This is kitchen", ap.select_room(2).get_remark());
    XCTAssertThrows(ap.exclude_room(3));
    XCTAssertThrows(ap.exclude_room(-1));
    XCTAssertNoThrow(ap.exclude_room(1));
    XCTAssertEqual(1, ap.get_countOfRooms());
    XCTAssertEqualWithAccuracy(20, ap.get_area(), 0.01);
}

@end
