-- Retrieve the titles and release years of movies that have 'Harry Potter' in their title, sorted by year
SELECT title, year  -- Selects the 'title' and 'year' columns from the 'movies' table
FROM movies  -- Specifies the 'movies' table as the source of data
WHERE title LIKE "%Harry Potter%"  -- Filters the rows to include only those where the 'title' contains the substring 'Harry Potter'
ORDER BY year;  -- Sorts the result set in ascending order by the 'year' column
