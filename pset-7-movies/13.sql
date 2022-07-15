SELECT peopleX.name
FROM(
    SELECT movie_id AS movie_idY
    FROM people peopleY
    INNER JOIN stars starsY ON peopleY.id = starsY.person_id
    WHERE peopleY.name = 'Kevin Bacon' AND peopleY.birth = 1958
)
INNER JOIN stars starsX ON movie_idY = starsX.movie_id
INNER JOIN people peopleX ON peopleX.id = starsX.person_id
WHERE peopleX.name <> 'Kevin Bacon' OR peopleX.birth <> 1958
GROUP BY peopleX.name