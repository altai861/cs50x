-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description from crime_scene_reports where year = 2021 and month = 7 and day = 28 and street = "Humphrey Street";
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
--| Littering took place at 16:36. No known witnesses.

SELECT transcript from interviews where year = 2021 and month = 7 and day = 28;

--Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
--| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

SELECT name from people join bakery_security_logs on people.license_plate = bakery_security_logs.license_plate where year = 2021 and month = 7 and day = 28 hour = 10 and minute >= 15 and minute <= 25 and activity = "exit";

--Vanessa || Bruce   | Barry   | Luca    |Sofia   |Iman    |Diana   |Kelsey  |

-- now we have to find the people who withdrew money from Leggett street atm earlier that morning

SELECT name from people join bank_accounts on people.id = bank_accounts.person_id join atm_transactions
on atm_transactions.account_number = bank_accounts.account_number where year = 2021 and month = 7 and day = 28 and atm_location = "Leggett Street" and transaction_type = "withdraw";

-- Bruce Diana Brooke Kenny Iman Luca Taylor Benista

-- Bruce Diana Iman Luca
-- these four are the interseptions

SELECT name from people join phone_calls on people.phone_number = phone_calls.caller where year = 2021 and month = 7 and day = 28 and duration < 60;

-- Bruce and Diana Left

SELECT name from people join phone_calls on people.phone_number = phone_calls.receiver where year = 2021 and month = 7 and day = 28 and duration < 60 and caller = (SELECT phone_number from people where name = "Bruce");

-- Bruce called Robin

SELECT name from people join phone_calls on people.phone_number = phone_calls.receiver where year = 2021 and month = 7 and day = 28 and duration < 60 and caller = (SELECT phone_number from people where name = "Diana");

-- Diana called Philip


SELECT city, hour, minute from airports join flights on airports.id = flights.destination_airport_id
where year = 2021 and month = 7 and day = 29 and origin_airport_id = (SELECT id from airports where city = "Fiftyville");

-- The earliest flight is to New york city at 8 20

SELECT id from airports where city = "New York City";
-- id is 4

SELECT id from airports where city = "Fiftyville";
-- id is 8

SELECT id from flights where origin_airport_id = 8 and destination_airport_id = 4 and year = 2021 and month = 7 and day = 29 and hour = 8 and minute = 20;
-- id is 36
SELECT name from people join passengers on people.passport_number = passengers.passport_number where flight_id = 36;

-- Only Bruce left here