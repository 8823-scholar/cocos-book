//
//  Animation_iOS_Tests.m
//  Animation iOS Tests
//
//  Created by 木内 智史 on 2014/06/24.
//
//

#import <XCTest/XCTest.h>
#include "Calculator.h"

@interface Animation_iOS_Tests : XCTestCase

@end

@implementation Animation_iOS_Tests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testCalculatorSum
{
    auto cal = new Calculator();
    XCTAssertEqual(cal->sum(1,2), 3);
}

@end
