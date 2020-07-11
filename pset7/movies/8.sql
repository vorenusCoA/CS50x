SELECT name
  FROM Movies
  JOIN Stars ON Movies.id = Stars.movie_id
  JOIN People ON Stars.person_id = People.id
WHERE title = 'Toy Story'