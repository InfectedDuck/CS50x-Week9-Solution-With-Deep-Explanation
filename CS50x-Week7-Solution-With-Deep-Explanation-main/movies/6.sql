-- Calculate the average rating of movies released in the year 2012
SELECT AVG(rating)  -- Calculates the average value of the 'rating' column
FROM ratings  -- Specifies the 'ratings' table as the source of data
JOIN movies ON movies.id = ratings.movie_id  -- Joins the 'ratings' table with the 'movies' table based on the matching 'movie_id'
WHERE movies.year = 2012;  -- Filters the rows to include only those where the 'year' of the movie is 2012
