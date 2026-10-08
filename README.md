# FRIENDGRAPH

FRIENDGRAPH is a college DSA project: a pure C11 graph/recommendation engine with a separate vanilla HTML/CSS/ES-module website. All graph traversal, friend intersections, recommendation scoring, sorting, hashing, queues, heaps, trie lookup and connected components run in C. The browser calls the HTTP API and renders its JSON. The interface uses an original cream grid-paper and wine-red visual style; the attached screenshot was used only as a style reference.

## Build and run

### Linux

Install GCC and GNU Make (`build-essential` on Debian/Ubuntu), then:

```sh
cd friendgraph/backend
make
make test
./friendgraph
```

### Windows

Install MSYS2/MinGW-w64 with GCC, Make and the MinGW UCRT environment. In the MinGW shell:

```sh
cd friendgraph/backend
make
make test
./friendgraph.exe
```

`make run` builds and launches the server. It serves the frontend from `../frontend` and listens on port 8080. Open **http://localhost:8080**. Keep the server's working directory at `backend` so the relative frontend and CSV paths resolve. `make test` runs the graph/data-structure assertions and recommendation scoring assertions.

Demo login names are `student01` through `student30` (Aarav Mehta through Aman Gill). The initial 30-user, five-interest-per-user dataset is in `backend/data/users.csv`; friend edges and requests are loaded from and saved to `backend/data/edges.csv` and `backend/data/requests.csv`.

## API examples

Run these while the server is active. The examples use `student01`, `student03`, and numeric user IDs for write payloads.

```sh
curl http://localhost:8080/api/health
curl -X POST http://localhost:8080/api/login -H 'Content-Type: application/json' -d '{"username":"student01"}'
curl http://localhost:8080/api/users
curl 'http://localhost:8080/api/dashboard?user=student01'
curl 'http://localhost:8080/api/recommendations?user=student01&limit=10&maxDistance=3'
curl 'http://localhost:8080/api/network?user=student01'
curl 'http://localhost:8080/api/requests?user=student01'
curl -X POST http://localhost:8080/api/requests/send -H 'Content-Type: application/json' -d '{"from":0,"to":8}'
curl -X POST http://localhost:8080/api/requests/respond -H 'Content-Type: application/json' -d '{"user":8,"id":1,"action":"accept"}'
curl -X POST http://localhost:8080/api/friends/remove -H 'Content-Type: application/json' -d '{"user":0,"from":0,"to":1}'
curl -X POST http://localhost:8080/api/undo -H 'Content-Type: application/json' -d '{"user":0}'
curl 'http://localhost:8080/api/search?user=student01&q=student0'
curl 'http://localhost:8080/api/path?user=student01&target=student09'
curl 'http://localhost:8080/api/visualize?user=student01&target=student09'
curl http://localhost:8080/api/stats
```

Additional analysis endpoints: `/api/common?user=student01&target=student03`, `/api/top-users?limit=10`, and `/api/communities`. `POST /api/block` accepts `{"user":0,"target":8,"action":"block"}` or `action: "unblock"`. Every API JSON response includes `engine_us`.

## Recommendation score

Candidates are BFS-reachable at distance 2 or 3, excluding existing friends and blocked users. C computes `mutual × 10 + distance bonus (20 at distance 2, 8 at distance 3) + shared interests × 5 − 15 for a previously declined request`. The max heap returns the highest scores. Each API record includes the mutual-friend names, path, distance and score breakdown.
