SELECT title
FROM(
    SELECT movies.title, COUNT(movies.title) AS i
    FROM movies
    INNER JOIN stars ON movies.id = stars.movie_id
    INNER JOIN people ON people.id = stars.person_id
    WHERE people.name = 'Johnny Depp' OR people.name = 'Helena Bonham Carter'
    GROUP BY movies.title
)
WHERE i = 2;