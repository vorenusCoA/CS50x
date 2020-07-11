SELECT name
  FROM Movies
  JOIN Stars ON Movies.id = Stars.movie_id
  JOIN People ON Stars.person_id = People.id
WHERE name != 'Kevin Bacon'
  AND Movies.id IN (SELECT Movies.id
                    FROM Movies
                    JOIN Stars ON Movies.id = Stars.movie_id
                    JOIN People ON Stars.person_id = People.id
                    WHERE name = 'Kevin Bacon'
                      AND birth = 1958)
GROUP BY name