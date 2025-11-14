-- Retrieve the titles of movies that star both 'Bradley Cooper' and 'Jennifer Lawrence'
SELECT movies.title  -- Selects the 'title' column from the 'movies' table
FROM stars  -- Specifies the 'stars' table as one of the tables to query
JOIN movies ON movies.id=stars.movie_id  -- Joins 'stars' table with 'movies' table based on matching movie IDs
JOIN people ON people.id=stars.person_id  -- Joins 'stars' table with 'people' table based on matching person IDs
-- Filters results to include only movies that star both 'Bradley Cooper' and 'Jennifer Lawrence'
WHERE stars.movie_id IN (
    SELECT movie_id  -- Subquery to get movie IDs starring 'Bradley Cooper'
    FROM stars  -- Specifies the 'stars' table
    JOIN people ON people.id=stars.person_id  -- Joins 'stars' table with 'people' table based on matching person IDs
    WHERE people.name='Bradley Cooper'  -- Filters to include only movies starring 'Bradley Cooper'
)
AND stars.movie_id IN (
    SELECT movie_id  -- Subquery to get movie IDs starring 'Jennifer Lawrence'
    FROM stars  -- Specifies the 'stars' table
    JOIN people ON people.id=stars.person_id  -- Joins 'stars' table with 'people' table based on matching person IDs
    WHERE people.name='Jennifer Lawrence'  -- Filters to include only movies starring 'Jennifer Lawrence'
);
