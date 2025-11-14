-- Retrieve the names of the top 5 longest songs from the 'songs' table
SELECT name  -- Selects the 'name' column from the 'songs' table
FROM songs  -- Specifies the 'songs' table as the source of data
ORDER BY duration_ms DESC  -- Orders the results by the 'duration_ms' column in descending order
LIMIT 5;  -- Limits the result set to the top 5 rows
