-- Retrieve the birth year of a person named 'Emma Stone'
SELECT birth  -- Selects the 'birth' column from the 'people' table
FROM people  -- Specifies the 'people' table as the source of data
WHERE name = 'Emma Stone';  -- Filters the rows to include only those where the 'name' column matches 'Emma Stone'
