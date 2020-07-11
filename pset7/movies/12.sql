SELECT title
  FROM Movies
  JOIN Stars ON Movies.id = Stars.movie_id
  JOIN People ON Stars.person_id = People.id
WHERE name = 'Johnny Depp'
  AND Movies.id IN (SELECT Movies.id
                    FROM Movies
                    JOIN Stars ON Movies.id = Stars.movie_id
                    JOIN People ON Stars.person_id = People.id
                    WHERE name = 'Helena Bonham Carter')