-- Retrieve the names of songs from the 'songs' table that have high danceability, energy, and valence
SELECT name  -- Selects the 'name' column from the 'songs' table
FROM songs  -- Specifies the 'songs' table as the source of data
WHERE danceability > 0.75  -- Filters songs to include only those with danceability greater than 0.75
AND energy > 0.75  -- Further filters songs to include only those with energy greater than 0.75
AND valence > 0.75;  -- Further filters songs to include only those with valence greater than 0.75
