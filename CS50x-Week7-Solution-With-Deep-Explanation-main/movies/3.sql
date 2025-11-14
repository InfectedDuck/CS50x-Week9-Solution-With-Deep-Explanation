-- Retrieve the titles of movies released from 2018 onwards and sort them alphabetically
SELECT title  -- Selects the 'title' column from the 'movies' table
FROM movies  -- Specifies the 'movies' table as the source of data
WHERE year >= 2018  -- Filters the rows to include only those where the 'year' is 2018 or later
ORDER BY title;  -- Sorts the result set in ascending alphabetical order by the 'title' column
