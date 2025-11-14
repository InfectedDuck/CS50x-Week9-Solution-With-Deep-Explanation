-- Retrieve the names of people who directed movies with a rating of 9.0 or higher
SELECT DISTINCT people.name  -- Selects unique names from the 'people' table
FROM directors  -- Specifies the 'directors' table as one of the tables to query
JOIN people ON directors.person_id=people.id  -- Joins 'directors' table with 'people' table based on matching IDs
-- Filters results to include only movies with a rating of 9.0 or higher
WHERE movie_id IN (
    SELECT id  -- Subquery to get movie IDs with high ratings
    FROM movies  -- Specifies the 'movies' table
    JOIN ratings ON ratings.movie_id=movies.id  -- Joins 'movies' table with 'ratings' table based on movie IDs
    WHERE ratings.rating>=9.0  -- Filters to include only movies with a rating of 9.0 or higher
);
