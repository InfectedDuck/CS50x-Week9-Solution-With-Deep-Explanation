-- Calculate the average energy level of all songs by the artist named "Drake"
SELECT AVG(energy)  -- Computes the average value of the 'energy' column
FROM songs  -- Specifies the 'songs' table as the primary source of data
JOIN artists ON songs.artist_id=artists.id  -- Joins 'songs' table with 'artists' table using a common column
WHERE artists.name = "Drake";  -- Filters results to include only songs by the artist "Drake"
