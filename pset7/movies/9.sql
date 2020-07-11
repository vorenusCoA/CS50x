SELECT name
  FROM Movies
  JOIN Stars ON Movies.id = Stars.movie_id
  JOIN People ON Stars.person_id = People.id
  WHERE year = 2004
GROUP BY name
ORDER BY birth