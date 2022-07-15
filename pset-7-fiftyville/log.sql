-- Keep a log of any SQL queries you execute as you solve the mystery.

-- airports              crime_scene_reports   people
-- atm_transactions      flights               phone_calls
-- bakery_security_logs  interviews
-- bank_accounts         passengers

SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2021 AND street = 'Humphrey Street'; -- Result - Theft at bakery 3 withnesses - 10:15am

SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2021 AND transcript LIKE '%bakery%'; -- Result 4 interviews ?

-- Seems to be on other case: Emma - I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.

-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

SELECT people.name, people.license_plate, people.passport_number
FROM bakery_security_logs
INNER JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute >= 15 AND minute <= 25
AND activity = 'exit'; -- Result: 8 suspects

-- +---------+---------------+-----------------+
-- |  name   | license_plate | passport_number |
-- +---------+---------------+-----------------+
-- | Vanessa | 5P2BI95       | 2963008352      |<--
-- | Bruce   | 94KL13X       | 5773159633      |<--
-- | Barry   | 6P58WS2       | 7526138472      |<--
-- | Luca    | 4328GD8       | 8496433585      |<--
-- | Sofia   | G412CB7       | 1695452385      |<--
-- | Iman    | L93JTIZ       | 7049073643      |<--
-- | Diana   | 322W7JE       | 3592750733      |<--
-- | Kelsey  | 0NTHK55       | 8294398571      |<--
-- +---------+---------------+-----------------+

-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

SELECT people.name, people.license_plate, people.passport_number FROM atm_transactions
INNER JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
INNER JOIN people ON people.id = bank_accounts.person_id
WHERE atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
AND year = 2021 AND month = 7 AND day = 28; -- Result: 4 suspects

-- +---------+---------------+-----------------+
-- |  name   | license_plate | passport_number |
-- +---------+---------------+-----------------+
-- | Bruce   | 94KL13X       | 5773159633      |<--
-- | Diana   | 322W7JE       | 3592750733      |<--
-- | Brooke  | QX4YZN3       | 4408372428      |
-- | Kenny   | 30G67EN       | 9878712108      |
-- | Iman    | L93JTIZ       | 7049073643      |<--
-- | Luca    | 4328GD8       | 8496433585      |<--
-- | Taylor  | 1106N58       | 1988161715      |
-- | Benista | 8X428L0       | 9586786673      |
-- +---------+---------------+-----------------+

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT people.name, people.license_plate, people.passport_number, airports.city FROM people
INNER JOIN phone_calls ON phone_calls.caller = people.phone_number
INNER JOIN passengers ON passengers.passport_number = people.passport_number
INNER JOIN flights ON flights.id = passengers.flight_id
INNER JOIN airports ON airports.id = flights.destination_airport_id
WHERE phone_calls.duration < 60 AND phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28
AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29
AND NOT airports.city = 'Fiftyville'
ORDER BY flights.hour, flights.minute ASC; -- Result: 2 suspects

-- +--------+---------------+-----------------+---------------+
-- |  name  | license_plate | passport_number |     city      |
-- +--------+---------------+-----------------+---------------+
-- | Sofia  | G412CB7       | 1695452385      | New York City |
-- | Bruce  | 94KL13X       | 5773159633      | New York City |<-- Early flight of 29.07.2021 - so it must be him.
-- | Kelsey | 0NTHK55       | 8294398571      | New York City |
-- | Kelsey | 0NTHK55       | 8294398571      | New York City |
-- | Taylor | 1106N58       | 1988161715      | New York City |
-- | Kenny  | 30G67EN       | 9878712108      | New York City |
-- | Diana  | 322W7JE       | 3592750733      | Boston        |<--
-- +--------+---------------+-----------------+---------------+

SELECT peopleR.name, peopleR.license_plate, peopleR.passport_number FROM phone_calls
INNER JOIN people peopleC ON peopleC.phone_number = phone_calls.caller
INNER JOIN people peopleR ON peopleR.phone_number = phone_calls.receiver
WHERE phone_calls.duration < 60 AND phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28
AND peopleC.passport_number = 5773159633;

-- +-------+---------------+-----------------+
-- | name  | license_plate | passport_number |
-- +-------+---------------+-----------------+
-- | Robin | 4V16VO0       |                 |
-- +-------+---------------+-----------------+