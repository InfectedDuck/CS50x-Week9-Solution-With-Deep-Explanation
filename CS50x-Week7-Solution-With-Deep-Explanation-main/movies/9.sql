-- Retrieve the distinct names of people who starred in movies released in 2004, ordered by their birth year
SELECT DISTINCT people.name  -- Selects the distinct 'name' column from the 'people' table to ensure no duplicate names
FROM stars  -- Specifies the 'stars' table as the source of data
JOIN people ON stars.person_id = people.id  -- Joins the 'stars' table with the 'people' table on the 'person_id'
WHERE stars.movie_id IN (  -- Filters rows to include only those where 'movie_id' matches the result of the subquery
    SELECT id  -- Selects the 'id' column from the 'movies' table
    FROM movies  -- Specifies the 'movies' table as the source of data
    WHERE year = 2004  -- Filters rows to include only movies released in the year 2004
)
ORDER BY people.birth;  -- Orders the result set by the 'birth' column in ascending order
