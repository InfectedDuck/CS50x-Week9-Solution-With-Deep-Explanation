-- Retrieve the titles of movies starring 'Chadwick Boseman', ordered by their ratings in descending order
SELECT movies.title  -- Selects the 'title' column from the 'movies' table
FROM stars  -- Specifies the 'stars' table as one of the tables to query
JOIN movies ON movies.id=stars.movie_id  -- Joins 'stars' table with 'movies' table based on matching movie IDs
JOIN people ON people.id=stars.person_id  -- Joins 'stars' table with 'people' table based on matching person IDs
JOIN ratings ON ratings.movie_id=stars.movie_id  -- Joins 'ratings' table with 'movies' table based on matching movie IDs
-- Filters results to include only movies starring 'Chadwick Boseman'
WHERE people.name='Chadwick Boseman'
-- Orders the results by the movie ratings in descending order
ORDER BY ratings.rating DESC
-- Limits the results to the top 5 highest-rated movies
LIMIT 5;
