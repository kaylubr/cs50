-- For crime scene reports
SELECT description
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';

-- For witnesses
SELECT name, transcript
FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28;

-- For people who was at the crime scene in the bakery within 10:15-10:25
SELECT * FROM bakery_security_logs
WHERE year = 2023
AND month = 7
AND day = 28
AND hour = 10
AND minute <= 25
AND activity = 'exit';

-- To know the names of people who was out in the scene within 10:15-10:25
SELECT * FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute <= 25
    AND activity = 'exit'
);

-- To know who was withdrawing at the ATM machine in Leggett Street
SELECT * FROM atm_transactions
WHERE year = 2023
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- To know their person id
SELECT * FROM bank_accounts
WHERE account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
);

-- To know their names based on their person_id
SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
);

-- Combine two lists of suspects from bakery and atm
SELECT * FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute <= 25
    AND activity = 'exit'
)
AND id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
);

-- To know who called who
SELECT * FROM phone_calls
WHERE caller IN (
    SELECT phone_number FROM people
    WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute <= 25
        AND activity = 'exit'
    )
    AND id IN (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number FROM atm_transactions
            WHERE year = 2023
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
        )
    )
)
AND year = 2023
AND month = 7
AND day = 28
AND duration <= 60;

-- To know the last 4 suspects name
SELECT * FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE caller IN (
        SELECT phone_number FROM people
        WHERE license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute <= 25
            AND activity = 'exit'
        )
        AND id IN (
            SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                WHERE year = 2023
                AND month = 7
                AND day = 28
                AND atm_location = 'Leggett Street'
                AND transaction_type = 'withdraw'
            )
        )
    )
    AND year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
)
OR phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE caller IN (
        SELECT phone_number FROM people
        WHERE license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute <= 25
            AND activity = 'exit'
        )
        AND id IN (
            SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                WHERE year = 2023
                AND month = 7
                AND day = 28
                AND atm_location = 'Leggett Street'
                AND transaction_type = 'withdraw'
            )
        )
    )
    AND year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
);

-- To know Fiftyville's airport info
SELECT * FROM airports
WHERE city = 'Fiftyville';

-- To know the earliest flight in fiftyville's airport
SELECT * FROM flights
WHERE origin_airport_id IN (
    SELECT id FROM airports
    WHERE city = 'Fiftyville'
)
AND year = 2023
AND month = 7
AND day = 29
ORDER BY hour
LIMIT 1;

-- To know the passengers name
SELECT * FROM passengers
WHERE flight_id = (
    SELECT id FROM flights
    WHERE origin_airport_id IN (
        SELECT id FROM airports
        WHERE city = 'Fiftyville'
    )
    AND year = 2023
    AND month = 7
    AND day = 29
    ORDER BY hour
    LIMIT 1
);

SELECT * FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE origin_airport_id IN (
            SELECT id FROM airports
            WHERE city = 'Fiftyville'
        )
        AND year = 2023
        AND month = 7
        AND day = 29
        ORDER BY hour
        LIMIT 1
    )
);
