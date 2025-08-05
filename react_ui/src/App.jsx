import { Route, Routes} from 'react-router';
import Home from './views/Home'

export default function App() {
  return (
    <>
      <Routes>
        <Route path='/' element={<Home/>} />
      </Routes>
    </>
  );
}


