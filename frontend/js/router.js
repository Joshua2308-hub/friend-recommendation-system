export function route(){const raw=location.hash.slice(1)||'/';const[path,query]=raw.split('?');return{path:path.startsWith('/')?path:`/${path}`,query}}
