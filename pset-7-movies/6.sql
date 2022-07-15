SELECT AVG(rating)
FROM ratings
INNER JOIN movies ON movie_id = id
WHERE year = 2012;