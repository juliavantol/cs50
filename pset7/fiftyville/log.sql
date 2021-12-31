-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Look at the reports
SELECT * FROM crime_scene_reports;

-- Filter the reports on things mentioning the duck
SELECT * FROM crime_scene_reports WHERE description LIKE "%duck%";
-- 295|2020|7|28|Chamberlin Street|Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.

-- See if a interview mentions the duck
SELECT * FROM interviews WHERE transcript LIKE "%duck%";
-- They don't

-- See if someone mentions being at the crime scene
SELECT * FROM interviews WHERE transcript LIKE "%Chamberlin Street%";
-- They don't

-- Crime report of crime scene
SELECT * FROM crime_scene_reports WHERE street LIKE "%Chamberlin Street%";
-- Not much new

-- Check courthouse security logs around time of crime
SELECT * FROM courthouse_security_logs WHERE hour == 10 AND month == 7 AND day == 28 ORDER BY minute ASC;
-- Thief probably left right after 10:15 so these entries are of interest
-- 259|2020|7|28|10|14|entrance|13FNH73
-- 260|2020|7|28|10|16|exit|5P2BI95
-- 261|2020|7|28|10|18|exit|94KL13X
-- 262|2020|7|28|10|18|exit|6P58WS2
-- 263|2020|7|28|10|19|exit|4328GD8
-- 264|2020|7|28|10|20|exit|G412CB7

-- Investigate 5P2BI95 license plate 
SELECT * FROM people WHERE license_plate == "5P2BI95";
-- 260|2020|7|28|10|16|exit|5P2BI95
-- 221103|Patrick|(725) 555-4692|2963008352|5P2BI95

SELECT * FROM people WHERE license_plate == "94KL13X";
-- 261|2020|7|28|10|18|exit|94KL13X
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X

-- Patrick


-- 30|Patrick|2020|2|7|Its disappearance, however, was but momentary. With a rending, 
-- tearing sound, one of the broad, white stones turned over upon its side and 
-- left a square, gaping hole, through which streamed the light of a lantern. 
-- Over the edge there peeped a clean-cut, boyish face, which looked keenly about it, 
-- and then, with a hand on either side of the aperture, drew itself shoulder-high and 
-- waist-high, until one knee rested upon the edge. In another instant he stood at the side of 
-- the hole and was hauling after him a companion, lithe and small like himself, with a pale 
-- face and a shock of very red hair.

SELECT * FROM passengers WHERE passport_number IN (
    SELECT passport_number FROM people WHERE license_plate == "5P2BI95"
);
-- 2|2963008352|6C
-- 20|2963008352|6B
-- 39|2963008352|8C
-- So there are three seats under his passportnumber, two of which next to each other

SELECT * FROM flights WHERE id IN (
    SELECT flight_id FROM passengers WHERE passport_number == 2963008352
);
-- 2|2|8|2020|7|30|12|44
-- 20|6|8|2020|7|28|15|22
-- 39|5|8|2020|7|27|22|37

-- 28/7 was the day of the crime
-- From 6 airport to 8 airport
SELECT * FROM airports WHERE id == 6;
SELECT * FROM airports WHERE id == 8;
-- From    6|BOS|Logan International Airport|Boston
-- To      8|CSF|Fiftyville Regional Airport|Fiftyville
-- Date of crime Boston? That's where he flew from

-- Let's look at bank accounts from Patrick
SELECT * FROM bank_accounts WHERE person_id in (
    SELECT id FROM people WHERE passport_number == 2963008352
);
-- Nothing
SELECT * FROM phone_calls WHERE day = 28 AND month = 7;

-- Look at Patrick outgoing calls (725) 555-4692
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND caller LIKE "%(725) 555-4692%";
-- 257|(725) 555-4692|(821) 555-5262|2020|7|28|456

-- Who was he calling? (821) 555-5262
SELECT * FROM people WHERE phone_number LIKE "%(821) 555-5262%";
-- 632023|Amanda|(821) 555-5262|1618186613|RS7I6A0

-- So Patrick and Amanda are sus. Patrick was calling Amanda on the 28th of July
SELECT * FROM courthouse_security_logs WHERE month == 7 AND day == 28  AND license_plate LIKE "%RS7I6A0%" ORDER BY minute ASC;
-- 281|2020|7|28|15|6|exit|RS7I6A0
-- 277|2020|7|28|13|8|entrance|RS7I6A0

-- Check Amanda as passenger
SELECT * FROM passengers WHERE passport_number LIKE "%1618186613%";
-- Amanda:
-- 6|1618186613|2C
-- 25|1618186613|3B
-- 42|1618186613|4D

-- Patrick:
-- 2|2963008352|6C
-- 20|2963008352|6B
-- 39|2963008352|8C

-- Check bank account Amanda
SELECT * FROM bank_accounts WHERE person_id IN (
    SELECT id FROM people WHERE passport_number LIKE "%1618186613%"
);
-- 90209473|632023|2011

SELECT * FROM atm_transactions WHERE account_number == 90209473;
-- 165|90209473|2020|7|27|Carvalho Road|deposit|40
-- 245|90209473|2020|7|28|Humphrey Lane|withdraw|45
-- 476|90209473|2020|7|29|Carvalho Road|withdraw|30
-- 523|90209473|2020|7|29|Humphrey Lane|withdraw|55
-- 632|90209473|2020|7|30|Humphrey Lane|deposit|35
-- 748|90209473|2020|7|30|Fifer Street|deposit|50
-- 765|90209473|2020|7|30|Humphrey Lane|deposit|65
-- 767|90209473|2020|7|30|Carvalho Road|withdraw|70
-- 895|90209473|2020|7|31|Humphrey Lane|withdraw|55
-- 1027|90209473|2020|7|31|Humphrey Lane|deposit|20

-- Ernest not really sus
SELECT * FROM people WHERE license_plate == "94KL13X";
-- 261|2020|7|28|10|18|exit|94KL13X
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X

SELECT * FROM passengers WHERE passport_number IN (
    SELECT passport_number FROM people WHERE license_plate == "94KL13X"
);
-- 36|5773159633|4A

SELECT * FROM flights WHERE id IN (
    SELECT flight_id FROM passengers WHERE passport_number == 5773159633
);
-- 36|8|4|2020|7|29|8|20

-- Amber didn't fly so isn't sus
SELECT * FROM people WHERE license_plate == "6P58WS2";
--243696|Amber|(301) 555-4174|7526138472|6P58WS2

SELECT * FROM passengers WHERE passport_number = 7526138472;

-- 259|2020|7|28|10|14|entrance|13FNH73
SELECT * FROM people WHERE license_plate == "13FNH73";
-- 745650|Sophia|(027) 555-1068|3642612721|13FNH73]

SELECT * FROM passengers WHERE passport_number = 3642612721;
-- 6|3642612721|8A
-- 31|3642612721|9B
-- 43|3642612721|2C
SELECT * FROM flights WHERE id IN (
    SELECT flight_id FROM passengers WHERE passport_number == 3642612721
);
-- 6|8|5|2020|7|28|13|49
SELECT * FROM airports WHERE id == 8;
SELECT * FROM airports WHERE id == 5;
-- 8|CSF|Fiftyville Regional Airport|Fiftyville
-- 5|DFS|Dallas/Fort Worth International Airport|Dallas

-- Amanda and Sophia were on the same flight
-- Sophia is very sus, she went in right before and flew the same day from Fiftyville to Dallas on seat 8A
SELECT * FROM phone_calls WHERE receiver LIKE "%(027) 555-1068%";
-- 183|(994) 555-3373|(027) 555-1068|2020|7|27|194
SELECT * FROM phone_calls WHERE receiver LIKE "%(027) 555-1068%";
SELECT * FROM people WHERE phone_number == "(994) 555-3373";
-- 652412|Denise|(994) 555-3373|4001449165|NRYN856
-- Sophia had a long phonecall with Denise the night before

SELECT * FROM courthouse_security_logs WHERE license_plate == "NRYN856";
-- 269|2020|7|28|10|42|entrance|NRYN856
-- 287|2020|7|28|17|11|exit|NRYN856

-- look for long phonecalls for plotting
SELECT avg(duration) FROM phone_calls;
-- 304
SELECT * FROM phone_calls WHERE day == 28 AND month == 7;

SELECT * FROM courthouse_security_logs WHERE hour > 9 AND month == 7 AND day == 28 ORDER BY hour ASC;

-- Look for recently made bank accounts
-- Sara, David, Charlotte and Amy
SELECT * FROM bank_accounts WHERE creation_year == 2020;
-- 37409101|440007|2020
-- 59116006|681821|2020
-- 15871517|639344|2020
-- 40237163|953420|2020

SELECT * FROM people WHERE id IN (
    SELECT person_id FROM bank_accounts WHERE account_number == 40237163
);
-- 440007|Sara|(340) 555-8872|3412604728|99A843C
-- 681821|David|(260) 555-0610|8834222028|SF5001S
-- 639344|Charlotte|(455) 555-5315|7226911797|Z5FH038
-- 953420|Amy|(670) 555-8598|9355133130|

-- Names from people at the courthouse around 10
SELECT name FROM people WHERE license_plate IN (
    SELECT license_plate FROM courthouse_security_logs WHERE hour > 9 AND month == 7 AND day == 28
);
-- Patrick
-- Amber
-- Brandon
-- Elizabeth
-- Roger
-- Madison
-- Danielle
-- Russell
-- Evelyn
-- Vincent
-- Mary
-- Amanda
-- Denise
-- Thomas
-- John
-- Ethan
-- Ernest
-- Sophia
-- Judith
-- Jeremy
-- Daniel
-- Frank

-- Flights out of Fiftyville
SELECT id FROM airports WHERE city == "Fiftyville";
-- 8

SELECT * FROM flights WHERE origin_airport_id == 8 AND DAY == 29 ORDER BY hour DESC;
-- 18|8|6|2020|7|29|16|0 Boston
-- 53|8|9|2020|7|29|15|20 Tokyo
-- 23|8|11|2020|7|29|12|15 SF
-- 43|8|1|2020|7|29|9|30 Chicago
-- 36|8|4|2020|7|29|8|20 London

SELECT city FROM airports WHERE id == 4;
-- London first flight on the 29th was to London

-- ATM locations
SELECT distinct(atm_location) FROM atm_transactions;
-- Humphrey Lane
-- Daboin Sanchez Drive
-- Carvalho Road
-- Fifer Street
-- Blumberg Boulevard

SELECT avg(amount) FROM atm_transactions;
SELECT * FROM atm_transactions WHERE amount > 52 AND day == 28 ORDER BY account_number ASC;

-- Check all the interviews for a mention of an ATM location
SELECT * FROM interviews WHERE transcript LIKE "%Fifer Street%";
-- 162|Eugene|2020|7|28|I don't know the thief's name, but it was someone I recognized. 
-- Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer 
--Street and saw the thief there withdrawing some money.

-- THIEF WAS WITHDRAWING MONEY AT FIFER STREET EARLY IN THE MORNING 28
SELECT * FROM interviews WHERE transcript LIKE "%thief%";
-- 163|Raymond|2020|7|28|As the thief was leaving the courthouse, they called someone who talked 
-- to them for less than a minute. In the call, I heard the thief say that they were planning to take 
-- the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the 
-- other end of the phone to purchase the flight ticket.

-- PHONECALL LESS THAN A MINUTE, EARLIEST FLIGHT OUT OF FIFTYVILLE (LONDON) RECEIVER BOUGHT TICKET
SELECT * FROM atm_transactions WHERE atm_location == "Fifer Street" AND transaction_type == "withdraw" AND day == 28;
-- account number
-- 246|28500762|2020|7|28|Fifer Street|withdraw|48
-- 264|28296815|2020|7|28|Fifer Street|withdraw|20
-- 266|76054385|2020|7|28|Fifer Street|withdraw|60
-- 267|49610011|2020|7|28|Fifer Street|withdraw|50
-- 269|16153065|2020|7|28|Fifer Street|withdraw|80
-- 288|25506511|2020|7|28|Fifer Street|withdraw|20
-- 313|81061156|2020|7|28|Fifer Street|withdraw|30
-- 336|26013199|2020|7|28|Fifer Street|withdraw|35
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (
    SELECT account_number FROM atm_transactions WHERE atm_location == "Fifer Street" AND transaction_type == "withdraw" AND day == 28
)) AND
license_plate IN (
    SELECT license_plate FROM courthouse_security_logs WHERE hour > 9 AND month == 7 AND day == 28
);


-- Bobby
-- Elizabeth
-- Victoria
-- Madison
-- Roy
-- Danielle
-- Russell
-- Ernest

SELECT name FROM people WHERE license_plate IN (
    SELECT license_plate FROM courthouse_security_logs WHERE hour > 9 AND month == 7 AND day == 28
);

SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (
    SELECT account_number FROM atm_transactions WHERE atm_location == "Fifer Street" AND transaction_type == "withdraw" AND day == 28
)) AND
license_plate IN (
    SELECT license_plate FROM courthouse_security_logs WHERE hour > 9 AND month == 7 AND day == 28
);
-- These people withdrew money and left the courthouse in the hour of 10
-- Elizabeth
-- Madison
-- Danielle
-- Russell
-- Ernest


SELECT receiver FROM phone_calls WHERE caller IN (
SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (
    SELECT account_number FROM atm_transactions WHERE atm_location == "Fifer Street" AND transaction_type == "withdraw" AND day == 28
)) AND
license_plate IN (
    SELECT license_plate FROM courthouse_security_logs WHERE hour > 9 AND month == 7 AND day == 28
)
)
AND duration < 60 AND day == 28
;
-- three accomplice suspects 
-- (375) 555-8161  864400|Berthold|(375) 555-8161||4V16VO0   NOT SUS DOESN'T HAVE PASSPORT
-- (676) 555-6554   250277|James|(676) 555-6554|2438825627|Q13SVG6
-- (725) 555-3243  847116|Philip|(725) 555-3243|3391710505|GW362R6
-- who bought a ticket for the flight to london
-- 36|8|4|2020|7|29|8|20 London

SELECT passport_number FROM passengers WHERE flight_id == 36;
-- 7214083635
-- 1695452385
-- 5773159633
-- 1540955065
-- 8294398571
-- 1988161715
-- 9878712108
-- 8496433585

SELECT * FROM people WHERE phone_number LIKE "%(725) 555-3243%";
-- Philip or James

-- Who was being called
SELECT * FROM phone_calls WHERE receiver IN (
    SELECT phone_number FROM people WHERE passport_number IN (
    SELECT passport_number FROM passengers WHERE flight_id == 36
)) AND duration < 60 AND day == 28;

-- Sus phonecalls
-- (826) 555-1652
-- (130) 555-0289
-- (286) 555-6063
-- (389) 555-5198
-- (499) 555-9472
-- (328) 555-1152
-- (367) 555-5533
-- (066) 555-9701 -----

-- 279|(826) 555-1652|(066) 555-9701|2020|7|28|55
SELECT name FROM people WHERE phone_number == "(066) 555-9701";
-- Doris

SELECT name FROM people WHERE phone_number == "(826) 555-1652";
-- Bobby

-- phone nos of withdrawers
SELECT * FROM phone_calls WHERE caller IN (

SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (
    SELECT account_number FROM atm_transactions WHERE atm_location == "Fifer Street" AND transaction_type == "withdraw" AND day == 28
)) AND
license_plate IN (
    SELECT license_plate FROM courthouse_security_logs WHERE hour > 9 AND month == 7 AND day == 28
)
) AND day == 28 AND duration < 60;




-- 254|(286) 555-6063|(676) 555-6554|2020|7|28|43
-- 255|(770) 555-1861|(725) 555-3243|2020|7|28|49

SELECT phone_number FROM people WHERE passport_number IN ( SELECT passport_number FROM passengers WHERE flight_id == 36);

SELECT name FROM people WHERE phone_number == "(375) 555-8161";
-- 233|(367) 555-5533|(375) 555-8161|2020|7|28|45  con duo

