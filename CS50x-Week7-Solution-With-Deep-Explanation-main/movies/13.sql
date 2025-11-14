-- Retrieve names of people who acted in the same movies as 'Kevin Bacon' but are not 'Kevin Bacon' themselves
SELECT name  -- Selects the 'name' column from the 'people' table
FROM people  -- Specifies the 'people' table as the source of data
-- Filters results to include only people who acted in movies with 'Kevin Bacon' but are not 'Kevin Bacon' themselves
WHERE id IN (
    SELECT person_id  -- Subquery to get the IDs of people who acted in certain movies
    FROM stars  -- Specifies the 'stars' table, which links people and movies
    WHERE movie_id IN (
        SELECT movie_id  -- Subquery to get the IDs of movies featuring a specific person
        FROM stars  -- Specifies the 'stars' table
        WHERE person_id = (
            SELECT id  -- Subquery to get the ID of 'Kevin Bacon'
            FROM people  -- Specifies the 'people' table
            WHERE name = 'Kevin Bacon'  -- Filters to include 'Kevin Bacon'
            AND birth = 1958  -- Filters to include only the person born in 1958
        )
    )
)
AND name != 'Kevin Bacon';  -- Further filter to exclude 'Kevin Bacon' from the results
