const use_sample = true;
const Max_Results = 25;
let currentShows = [];

const sample_show = [
    {title: "Breaking Bad", year: 2000, rating: 9.5, seasons: 5, episodes: 62, genre: "Crime, Drama"},
    {title: "Loki", year: 2022, rating: 8.2, seasons: 2, episodes: 12, genre: "Action, Adventure"}
];

function readQuery(){
    return{
        titlePrefix: document.getElementById("titlePrefix").value.trim(),
        genre: document.getElementById("genre").value,
        ratingMin: document.getElementById("ratingMin").value,
        yearMin: document.getElementById("yearMin").value,
        yearMax: document.getElementById("yearMax").value,
        seasonsMin: document.getElementById("seasonsMin").value,
        seasonsMax: document.getElementById("seasonsMax").value,
        sortBy: document.getElementById("sortBy").value,
        sortAlgo: document.getElementById("sortAlgo").value,
        descending: document.getElementById("descending").checked
    };
}

function searchSample(q){
    const start = performance.now();
    let shows = sample_show.filter(function(s){
        if(s.rating < Number(q.ratinMin)) return false;
        if(q.yearMin !== "" && s.year < Number(q.yearMin)) return false;
        if(q.yearMax !== "" && s.year > Number(q.yearMax)) return false;
        if(q.seasonsMin !== "" && s.seasons < Number(q.seasonsMax)) return false;
        if(q.seasonsMax !== "" && s.seasons > Number(q.seasonsMax)) return false;
        if(q.titlePrefix != "" && !s.title.toLowerCase().startsWith(q.titlePrefix.toLowerCase())) return false;
        if(q.genre !== "" && !s.genre.split(",").includes(q.genre)) return false;
        return true;
});

shows.sort(function(a,b){
  const x = a[q.sortBy];
  const y = b[q.sortBy];
  let result = 0;
  if(x <y) result = -1;
  else if (x>y) result =1;
  return q.descending ? - result : result;
});
    return {sortMs: performance.now() - start, total: shows.length, shows:shows};
}

//call sever
async function searchServer(q){
    const params = new URLSearchParams();
    for(const key in q){
        if(q[key] !== ""){
            params.set(key,q[key]);
        }
    }
    const response = await fetch("/api/search?" + params.toString());
    if(!response.ok){
        throw  new Error("Sever returned " + response.status);
    }
    return response.json();
}

//reesults s
function makeRow(show){
    const li = document.createElement("li");
    li.className = "show";
    const rating = document.createElement("div");
    rating.className = "rating";
    rating.textContent = Number(show.rating).toFixed(1);

    const info = document.createElement("div");
    const title=  document.createElement("h2");
    title.textContent = show.title;
    const meta = document.createElement("p");
    meta.className = "meta";
    meta.textContent = show.year + ", " + show.genre.split(",").join(", ");
    info.append(title, meta);

    const size = document.createElement("div");
    size.className = "size";
    size.textContent = show.seasons + (show.seasons === 1 ? " season, " : " seasons, ") + show.episodes + "episodes";

    li.append(rating,info,size);
    return li;
}

function showResults(data, q){
    currentShows = data.shows;
    document.getElementById("pick").hidden = true;

    const list = document.getElementById("list");
    const status = document.getElementById("status");
    list.replaceChildren();

    if(data.shows.length === 0){
        status.textContent = "No shows match :(";
        return;
    }

    const shown = Math.min(data.shows.length, Max_Results);
    for(let i =0; i < shown; i++){
        list.append(makeRow(data.shows[i]));

    }
    const source = use_sample ? " (sample data)" : "";  //testing
    status.textContent = data.total + "shows: " + shown + "sorted with: " + q.sortAlgo +
        " sorted in " + data.sortMs.toFixed(2) + " ms." +source;

}

function showPick(){
    if(currentShows.length === 0){
        document.getElementById("status").textContent = "No shows."
        return;
    }
    const show = currentShows[Math.floor(Math.random() * currentShows.length)];
    const box = document.getElementById("pick");
    box.replaceChildren();
    const label = document.createElement("p");
    label.className = "label";
    label.textContent = "Watch this :)";
    const title = document.createElement("h2");
    title.textContent = show.title;
    const meta = document.createElement("p");
    meta.textContent = show.year + ", rated " + Number(show.rating).toFixed(1); + ", " +
        show.seasons + (show.seasons === 1 ? " season" : "seasons");
    box.append(label, title, meta);
    box.hidden = false;
}

async function runSearch(){
      const q = readQuery();
      try{
          const data = use_sample ? searchSample(q) : await searchSever(q);
          showResults(data, q);
      }
      catch(error){
          document.getElementById("status").textContent = "Cant reach the sever";
      }
}

      document.getElementById("filters").addEventById("filters").addEventListener("sumbit",
          function(event) {
          event.preventDefault();
          runSearch();
          });
      document.getElementById("suprise").addEventListener("click", showPick);
      document.getElementById("ratingMin").addEventListener("input", function(event) {
          document.getElementById("ratingOut").textContent = Number(event.target.value).toFixed(1);
      });

      runSearch();