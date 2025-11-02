const express = require('express');
const redis = require('redis');

const app = express();
app.use(express.json());

const client = redis.createClient({
  socket: {
    host: 'redis',
    port: 6379
  }
});

client.connect().then(() => {
  console.log('Connected to Redis');
});

app.post('/events', async (req, res) => {
  try {
    const events = req.body;

    for (const event of events) {
      
      const fields = {};
      for (const [key, value] of Object.entries(event)) {
        fields[key] = typeof value === 'string' ? value : JSON.stringify(value);
      }
      
      await client.xAdd('super-cash-stream', '*', fields);
    }
    
    console.log(`Added ${events.length} events to stream`);
    res.json({ success: true, count: events.length });
  } catch (error) {
    console.error('Error:', error);
    res.status(500).json({ error: error.message });
  }
});

app.listen(3000, () => {
  console.log('API listening on port 3000');
});