-- Retrieve the ratings and titles of movies released in 2010, excluding rows with empty ratings, sorted by rating and then by title
SELECT rating, movies.title  -- Selects the 'rating' and 'title' columns to include in the result set
FROM ratings  -- Specifies the 'ratings' table as the source of rating data
JOIN movies ON movies.id = ratings.movie_id  -- Joins the 'ratings' table with the 'movies' table on the 'movie_id'
WHERE movies.year = 2010 AND ratings.rating != ""  -- Filters rows for movies released in 2010 and excludes rows with empty ratings
ORDER BY ratings.rating DESC, movies.title;  -- Sorts the results by 'rating' in descending order and then by 'title' in ascending order
