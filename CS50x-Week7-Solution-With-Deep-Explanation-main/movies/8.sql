-- Retrieve the names of people who starred in the movie "Toy Story"
SELECT people.name  -- Selects the 'name' column from the 'people' table
FROM stars  -- Specifies the 'stars' table as the source of data
JOIN people ON stars.person_id = people.id  -- Joins the 'stars' table with the 'people' table based on the 'person_id'
WHERE movie_id IN (  -- Filters rows to include only those where the 'movie_id' matches the result of the subquery
    SELECT id  -- Selects the 'id' column from the 'movies' table
    FROM movies  -- Specifies the 'movies' table as the source of data
    WHERE title = 'Toy Story'  -- Filters rows to include only those with the title 'Toy Story'
);
