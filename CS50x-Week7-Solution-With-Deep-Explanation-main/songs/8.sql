-- Retrieve the names of songs that include the term "feat" in their title
SELECT name  -- Selects the 'name' column from the 'songs' table
FROM songs  -- Specifies the 'songs' table as the source of data
WHERE name LIKE "%feat%";  -- Filters results to include only songs with "feat" in their title
