SELECT people.name
FROM people
INNER JOIN stars ON stars.person_id = people.id
INNER JOIN movies ON movies.id = stars.movie_id
WHERE movies.title = 'Toy Story';