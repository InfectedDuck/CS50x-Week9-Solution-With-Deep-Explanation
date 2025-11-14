-- Count the number of movies that have received a perfect rating of 10.0
SELECT COUNT(movie_id)  -- Counts the number of entries in the 'ratings' table where the condition is met
FROM ratings  -- Specifies the 'ratings' table as the source of data
WHERE rating = 10.0;  -- Filters the rows to include only those where the 'rating' is exactly 10.0
