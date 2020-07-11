SELECT AVG(rating)
  FROM Movies
  JOIN Ratings ON Movies.id = Ratings.movie_id
WHERE year = 2012