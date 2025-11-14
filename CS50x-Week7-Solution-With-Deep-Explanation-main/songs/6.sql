-- Retrieve the names of songs by the artist named "Post Malone"
SELECT name  -- Selects the 'name' column from the 'songs' table
FROM songs  -- Specifies the 'songs' table as the source of data
WHERE artist_id = (  -- Filters songs to include only those by a specific artist
    SELECT id  -- Retrieves the 'id' of the artist from the 'artists' table
    FROM artists  -- Specifies the 'artists' table as the source of data for the subquery
    WHERE name = "Post Malone"  -- Filters the artist to match the name "Post Malone"
);
