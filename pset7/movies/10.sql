SELECT name
  FROM Movies
  JOIN Ratings ON Movies.id = Ratings.movie_id
  JOIN Directors ON Movies.id = Directors.movie_id
  JOIN People ON Directors.person_id = People.id
WHERE rating >= 9.0
GROUP BY name